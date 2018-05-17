// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;
using System.Collections.Generic;
using Dormouse.Rincewind.Twoflower;
using Dormouse.Rincewind.Mapp;

namespace Dormouse.Rincewind
{
	public static class Program
	{
		public static void Main()
		{
			Brochure brochure = new Brochure(null);
			Game game = new Game(brochure);

			ItemResource coinsItem = new ItemResource(game);
			coinsItem.Create();
			coinsItem.Name = "Coins";
			coinsItem.Value = 1;

			ItemResource sardinesItem = new ItemResource(game);
			sardinesItem.Create();
			sardinesItem.Name = "Sardines";
			sardinesItem.Value = 10;

			SkillResource cookingSkill = new SkillResource(game);
			cookingSkill.Create();
			cookingSkill.Name = "Cooking";

			QuestStepResource startQuest = new QuestStepResource(game);
			startQuest.Create();
			startQuest.Name = "(Cook's Assistant) Start Quest";

			QuestStepResource getEggStep = new QuestStepResource(game);
			getEggStep.Create();
			getEggStep.Name = "(Cook's Assistant) Get large egg";
			getEggStep.AddSolution(startQuest);

			QuestStepResource getFlourStep = new QuestStepResource(game);
			getFlourStep.Create();
			getFlourStep.Name = "(Cook's Assistant) Get finely milled flour";
			getFlourStep.AddSolution(startQuest);

			QuestStepResource getMilkStep = new QuestStepResource(game);
			getMilkStep.Create();
			getMilkStep.Name = "(Cook's Assistant) Get prized milk";
			getMilkStep.AddSolution(startQuest);

			QuestStepResource finalStep = new QuestStepResource(game);
			finalStep.Create();
			finalStep.Name = "(Cook's Assistant) Make cake";
			finalStep.AddSolution(getEggStep, getFlourStep, getMilkStep);

			QuestResource cooksAssistantQuest = new QuestResource(game);
			cooksAssistantQuest.Create();
			cooksAssistantQuest.Name = "Cook's Assistant";
			cooksAssistantQuest.SetFinalStep(finalStep);

			Dictionary<SkillResource, float> xpReward = new Dictionary<SkillResource, float>();
			xpReward.Add(cookingSkill, 300.0f);
			cooksAssistantQuest.RewardXP = xpReward;

			brochure.Connect(new Requirement() { Count = 500, IsOutput = true }, cooksAssistantQuest.CompleteAction, coinsItem.Resource);
			brochure.Connect(new Requirement() { Count = 20, IsOutput = true }, cooksAssistantQuest.CompleteAction, sardinesItem.Resource);

			var deserializedCooksAssistantQuest = new QuestResource(game);
			deserializedCooksAssistantQuest.FromResource(cooksAssistantQuest.Resource);

			var resources = new ResourceCollection(brochure);
			foreach (var resource in resources.All())
			{
				Console.WriteLine("'{0}' (#{1}, {2})", resource.Name, resource.ID, resource.TypeName);

				var actions = new ResourceActionCollection(brochure, resource);
				foreach (var action in actions.All())
				{
					if (action.IsGetter)
					{
						Console.WriteLine("- get {0}", action.TypeName);
					}
					else
					{
						Console.WriteLine("- {0}", action.TypeName);
					}

					var requirements = new RequirementCollection(brochure, action);
					foreach (var requirement in requirements.All())
					{
						string type;
						if (requirement.IsInput && requirement.IsOutput)
						{
							type = "in/out [bad!]";
						}
						else if (requirement.IsInput)
						{
							type = "input";
						}
						else if (requirement.IsOutput)
						{
							type = "output";
						}
						else
						{
							type = "require";
						}

						Console.WriteLine("  * {0} '{1}' (#{2}, {3}) x{4}", type, requirement.Resource.Name, requirement.Resource.ID, requirement.Resource.TypeName, (int)Math.Ceiling(requirement.Count));
					}
				}
			}
		}
	}
}
