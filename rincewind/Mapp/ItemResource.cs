using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Dormouse.Rincewind.Twoflower;

namespace Dormouse.Rincewind.Mapp
{
	public class ItemResource : MappResource
	{
		public int Value
		{
			get
			{
				return Game.Brochure.GetUserdataInt32(Resource, "mapp-item-value") ?? 0;
			}
			set
			{
				Game.Brochure.SetUserdata(Resource, "mapp-item-value", value);
			}
		}

		public static string ToCategory(string value)
		{
			return value.ToLowerInvariant().Trim().Replace(' ', '-');
		}

		public bool MatchCategory(string value)
		{
			string category = "mapp-category-" + ToCategory(value);
			return Game.Brochure.HasTag(Resource, value);
		}

		public void AddCategory(string value)
		{
			string category = "mapp-category-" + ToCategory(value);
			Game.Brochure.AddTag(Resource, value);
		}

		public void RemoveCategory(string value)
		{
			string category = "mapp-category-" + ToCategory(value);
			Game.Brochure.RemoveTag(Resource, value);
		}

		public string[] GetCategories()
		{
			string[] tags = Game.Brochure.GetTags(Resource);
			List<string> categories = new List<string>();
			for (int i = 0; i < tags.Length; ++i)
			{
				if (tags[i].StartsWith("mapp-category-"))
				{
					string value = tags[i].Replace("mapp-category-", "");
					categories.Add(value);
				}
			}

			return categories.ToArray();
		}

		public ItemResource(Game game) : base(game)
		{
			// Nothing.
		}

		protected override void BeforeUpdate()
		{
			Game.SetResourceType(Resource, Game.ITEM_RESOURCE);
		}

		protected override bool TryFromResource(Resource resource)
		{
			if (!Game.IsResourceType(resource, Game.ITEM_RESOURCE))
			{
				return false;
			}
			
			// Nothing.

			return true;
		}
	}
}
