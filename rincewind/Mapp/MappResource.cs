// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;
using Dormouse.Rincewind.Twoflower;

namespace Dormouse.Rincewind.Mapp
{
	public abstract class MappResource : IDisposable
	{
		Resource mResource;
		public Resource Resource
		{
			get { return mResource; }
		}

		public string Name
		{
			get { return mResource.Name; }
			set
			{
				if (mResource.Name != value)
				{
					mResource.Name = value;
					Update();
				}
			}
		}

		public bool IsDisposed
		{
			get { return mResource == null || mResource.IsDisposed; }
		}

		public bool IsValid
		{
			get { return !IsDisposed && mResource.ID != 0; }
		}

		Game mGame;
		public Game Game
		{
			get { return mGame; }
		}

		public MappResource(Game game)
		{
			if (game == null)
			{
				throw new ArgumentNullException("game");
			}

			mGame = game;

			mResource = new Resource();
		}

		protected abstract void BeforeUpdate();

		protected void Update()
		{
			BeforeUpdate();
			Game.Brochure.Update(mResource);
		}

		public void Create()
		{
			if (mResource.ID != 0)
			{
				throw new InvalidOperationException(String.Format("{0} '#{1}' #{2} is already created.", GetType().Name, Resource.Name, Resource.ID));
			}

			BeforeUpdate();
			mResource = Game.Brochure.AddResource(mResource);
		}

		protected abstract bool TryFromResource(Resource resource);

		public void FromResource(Resource resource)
		{
			if (resource == null)
			{
				throw new ArgumentNullException("resource");
			}

			if (!TryFromResource(resource))
			{
				throw new InvalidOperationException(String.Format("Could not create {0} from resource '{1}' (#{2}).", GetType().Name, resource.Name, resource.ID));
			}

			mResource = resource;
		}

		~MappResource()
		{
			Dispose();
		}

		public virtual void Dispose()
		{
			if (!IsDisposed)
			{
				mResource.Dispose();
				mResource = null;

				GC.SuppressFinalize(this);
			}
		}
	}
}
