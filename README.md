# Discworld: A goal planner, route finder, and game relation database
Discworld is composed of two core components: **Twoflower** and **Mapp**.

**Twoflower** is the core component: it exposes a generic game relation database
(GameDB) and implements a goal planner (using a depth-first search) and route
finder (using A\*). The GameDB could be used to map relationships, such as the
XP rewarded for an action, the resources required to make an item, and so on.
You're really limited only by how well you can model these relationships in a
graph.

**Mapp** is a component that exposes the GameDB to Lua. It provides an interface to create resources, define their relationships, and so on
in a text-based format. This means that a GameDB can be constructed from Lua
code, which is great for source control! For an example of Mapp in action, see (https://github.com/aaronbolyard/itsyscape)[ItsyScape]'s ItsyScape.GameDB module and the corresponding construction script in Resources/Game/DB/Init.lua

## Copyright & License

Copyright Aaron Bolyard aka [bk]door.maus

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.