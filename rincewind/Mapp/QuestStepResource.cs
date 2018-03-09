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
	public class QuestStepResource : MappResource
	{
		public class Solution
		{
			QuestStepResource mParent;
			QuestStepResource Parent
			{
				get { return mParent; }
			}

			ResourceAction mAction;
			public ResourceAction Action
			{
				get { return mAction; }
			}

			public Solution(QuestStepResource parent, ResourceAction action)
			{
				mParent = parent;
				mAction = action;
			}

			public QuestStepResource[] GetPreviousSteps()
			{
				List<QuestStepResource> result = new List<QuestStepResource>();

				bool encounteredParentQuestStep = false;
				var requirements = new RequirementCollection(Parent.Game.Brochure, mAction);
				foreach (var requirement in requirements.All())
				{
					if (Parent.Game.IsResourceType(requirement.Resource, Game.QUEST_STEP_RESOURCE))
					{
						if (requirement.IsInput)
						{
							throw new InvalidOperationException(String.Format("QuestStepResource cannot be input; malformed requirement #{0} for action #{1}.", requirement.ID, Action.ID));
						}

						if (!requirement.IsOutput)
						{
							QuestStepResource resource = new QuestStepResource(Parent.Game);
							resource.FromResource(requirement.Resource);

							result.Add(resource);
						}
						else if (encounteredParentQuestStep)
						{
							throw new InvalidOperationException(String.Format("Cannot have multiple QuestStepResource outputs; malformed requirement #{0} for action #{1}.", requirement.ID, Action.ID));
						}
						else
						{
							if (requirement.Resource.ID != Parent.Resource.ID)
							{
								throw new InvalidOperationException(String.Format("Parent mismatch; malformed requirement #{0} for action #{1}.", requirement.ID, Action.ID));
							}

							encounteredParentQuestStep = true;
						}
					}
				}

				if (!encounteredParentQuestStep)
				{
					throw new InvalidOperationException(String.Format("No parent; malformed requirement action #{0}.", Action.ID));
				}

				return result.ToArray();
			}
		}

		List<Solution> mSolutions = new List<Solution>();
		public Solution[] Solutions
		{
			get { return mSolutions.ToArray(); }
		}

		public QuestStepResource(Game game) : base(game)
		{
			// Nothing.
		}

		protected override void BeforeUpdate()
		{
			Game.SetResourceType(Resource, Game.QUEST_STEP_RESOURCE);
		}

		protected override bool TryFromResource(Resource resource)
		{
			if (!Game.IsResourceType(resource, Game.QUEST_STEP_RESOURCE))
			{
				return false;
			}

			mSolutions = new List<Solution>();
			var actions = new ResourceActionCollection(Game.Brochure, resource);
			foreach (var action in actions.ByName(Game.QUEST_COMPLETE_ACTION))
			{
				mSolutions.Add(new Solution(this, action));
			}

			return true;
		}

		public Solution AddSolution(params QuestStepResource[] previousSteps)
		{
			return AddSolution(previousSteps.AsEnumerable());
		}

		public Solution AddSolution(IEnumerable<QuestStepResource> previousSteps)
		{
			ResourceAction solutionAction = new ResourceAction() { IsGetter = true };
			Game.SetActionDefinition(solutionAction, Game.QUEST_COMPLETE_ACTION);
			solutionAction = Game.Brochure.Connect(solutionAction, Resource);

			var outputRequirement = new Requirement() { IsOutput = true, Count = 1 };
			Game.Brochure.Connect(outputRequirement, solutionAction, Resource);

			foreach (var step in previousSteps)
			{
				if (step.IsValid)
				{
					var requirement = new Requirement() { Count = 1 };
					Game.Brochure.Connect(requirement, solutionAction, step.Resource);
				}
			}

			Solution solution = new Solution(this, solutionAction);
			mSolutions.Add(solution);

			return solution;
		}

		public bool RemoveSolution(Solution solution)
		{
			if (mSolutions.Remove(solution))
			{
				Game.Brochure.Remove(solution.Action);

				return true;
			}

			return false;
		}
	}
}
