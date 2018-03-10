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
using Dormouse.Rincewind.Twoflower;

namespace Dormouse.Rincewind.Mapp
{
	public class Game
	{
		Brochure mBrochure;

		public Brochure Brochure
		{
			get { return mBrochure; }
		}

		Dictionary<string, int> mResourceTypeIDs = new Dictionary<string, int>();
		public void SetResourceType(Resource resource, string name)
		{
			name = name?.ToLowerInvariant();

			int id;
			if (!mResourceTypeIDs.TryGetValue(name, out id))
			{
				throw new InvalidOperationException(String.Format("Resource type {0} not found; cannot assign to resource #{1} ('{2}').", name, resource.ID, resource.Name));
			}

			resource.TypeID = id;
			resource.TypeName = name;
		}

		public bool IsResourceType(Resource resource, string name)
		{
			name = name?.ToLowerInvariant();

			int id;
			if (!mResourceTypeIDs.TryGetValue(name, out id))
			{
				throw new InvalidOperationException(String.Format("Resource type {0} not found; cannot compare to resource #{1} ('{2}').", name, resource.ID, resource.Name));
			}

			return resource.TypeID == id;
		}

		Dictionary<string, int> mActionDefinitionIDs = new Dictionary<string, int>();
		public void SetActionDefinition(ResourceAction action, string name)
		{
			name = name?.ToLowerInvariant();

			int id;
			if (!mActionDefinitionIDs.TryGetValue(name, out id))
			{
				throw new InvalidOperationException(String.Format("Resource action definition {0} not found; cannot assign to action.", name));
			}

			action.TypeID = id;
			action.TypeName = name;
		}

		public Game(Brochure brochure)
		{
			if (brochure == null)
			{
				throw new ArgumentNullException("brochure");
			}

			mBrochure = brochure;
			ValidateBrochure();
		}

		public const string ITEM_RESOURCE = "item";
		public const string SKILL_RESOURCE = "skill";
		public const string QUEST_RESOURCE = "quest";
		public const string QUEST_STEP_RESOURCE = "quest_step";

		public const string QUEST_COMPLETE_ACTION = "quest.complete";

		void ValidateBrochure()
		{
			EnsureResourceType("item");
			EnsureResourceType("skill");
			EnsureResourceType("quest");
			EnsureResourceType("quest_step");

			EnsureActionType("quest.complete", true);
		}

		void EnsureResourceType(string name)
		{
			var types = mBrochure.GetResourceTypes(name);
			if (types.Length == 0)
			{
				int id = mBrochure.AddResourceType(name);
				mResourceTypeIDs.Add(name, id);
			}
			else if (types.Length == 1)
			{
				mResourceTypeIDs.Add(name, types[0]);
			}
			else
			{
				throw new InvalidOperationException(String.Format("Resource type {0} has multiple {1} definitions, expected 1.", name, types.Length));
			}
		}

		void EnsureActionType(string name, bool isGetter = false)
		{
			var actions = new ResourceActionCollection(mBrochure);
			var types = actions.Definitions().Where(r => r.TypeName == name).ToArray();
			if (types.Length == 0)
			{
				int id = mBrochure.AddActionDefinition(new ResourceAction() { TypeName = name, IsGetter = isGetter });
				mActionDefinitionIDs.Add(name, id);
			}
			else if (types.Length == 1)
			{
				mActionDefinitionIDs.Add(name, types[0].TypeID);
			}
			else
			{
				throw new InvalidOperationException(String.Format("Action definition {0} has multiple {1} instances, expected 1.", name, types.Length));
			}
		}
	}
}
