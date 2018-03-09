// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Dormouse.Rincewind.Twoflower;

namespace Dormouse.Rincewind.Mapp
{
	public class QuestResource : MappResource
	{
		ResourceAction mCompleteAction;
		public ResourceAction CompleteAction
		{
			get { return mCompleteAction; }
		}

		QuestStepResource mFinalStep;
		public QuestStepResource FinalStep
		{
			get { return mFinalStep; }
		}

		public QuestResource(Game game) : base(game)
		{
			// Nothing.
		}

		public void SetFinalStep(QuestStepResource resource)
		{
			if (!resource.IsValid)
			{
				throw new InvalidOperationException(String.Format("QuestStepResource not valid; cannot set as step for QuestResource '{0}' (#{1})", Name, Resource.ID));
			}

			// Remove current final step.
			if (mFinalStep != null)
			{
				var requirements = new RequirementCollection(Game.Brochure, mCompleteAction);

				// There should only be one requirement that matches this condition, but iterate anyway.
				foreach (var requirement in requirements.All().Where(r => r.Resource.ID == mFinalStep.Resource.ID))
				{
					Game.Brochure.Remove(requirement);
				}
			}

			// Create action, if necessary.
			if (mCompleteAction == null)
			{
				mCompleteAction = new ResourceAction() { IsGetter = true };
				Game.SetActionDefinition(mCompleteAction, Game.QUEST_COMPLETE_ACTION);

				mCompleteAction = Game.Brochure.Connect(mCompleteAction, Resource);

				// This quest should be an output. This ensures the goal planner functions as expected.
				Requirement outputRequirement = new Requirement() { IsOutput = true, Count = 1 };
				Game.Brochure.Connect(outputRequirement, mCompleteAction, Resource);
			}

			Requirement finalSepRequirement = new Requirement() { Count = 1 };
			Game.Brochure.Connect(finalSepRequirement, mCompleteAction, resource.Resource);
		}

		protected override void BeforeUpdate()
		{
			Game.SetResourceType(Resource, Game.QUEST_RESOURCE);
		}

		protected override bool TryFromResource(Resource resource)
		{
			if (!Game.IsResourceType(resource, Game.QUEST_RESOURCE))
			{
				return false;
			}

			QuestStepResource finalStep = null;
			var actions = new ResourceActionCollection(Game.Brochure, resource);
			foreach (var action in actions.ByName(Game.QUEST_COMPLETE_ACTION).Where(a => a.IsGetter))
			{
				if (finalStep != null)
				{
					throw new InvalidOperationException(String.Format("Multiple final steps for QuestResource {0} (#{1}).", resource.Name, resource.ID));
				}

				var requirements = new RequirementCollection(Game.Brochure, action);
				Resource finalStepResource = null;
				bool hasQuestAsOutput = false;
				foreach (var requirement in requirements.All())
				{
					if (Game.IsResourceType(requirement.Resource, Game.QUEST_STEP_RESOURCE))
					{
						if (finalStepResource != null)
						{
							throw new InvalidOperationException(String.Format("Multiple final steps for QuestResource {0} (#{1}) complete action (#{2}).", resource.Name, resource.ID, action.ID)));
						}

						if (requirement.IsInput || requirement.IsOutput)
						{
							throw new InvalidOperationException(String.Format("Final step cannot be input or output; bad requirement #{0}.", requirement.ID));
						}
		
						finalStepResource = requirement.Resource;
					}
					else if (Game.IsResourceType(requirement.Resource, Game.QUEST_RESOURCE) && requirement.IsOutput)
					{
						if (requirement.Resource.ID != resource.ID)
						{
							throw new InvalidOperationException(String.Format("Final step does not have QuestResource '${0}' #{1} as output; bad requirement #{2}.", resource.Name, resource.ID, requirement.ID));
						}

						if (hasQuestAsOutput)
						{
							throw new InvalidOperationException(String.Format("Duplicate QuestResource output for final step; bad requirement #{2}.", resource.Name, resource.ID, requirement.ID));
						}

						hasQuestAsOutput = true;
					}
				}

				finalStep = new QuestStepResource(Game);
				finalStep.FromResource(finalStepResource);
			}

			if (finalStep == null)
			{
				throw new InvalidOperationException(String.Format("No final step for QuestResource {0} (#{1}).", resource.Name, resource.ID));
			}
			else
			{
				mFinalStep = finalStep;
			}

			return true;
		}
	}
}
