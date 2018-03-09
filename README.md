# Discworld: A goal planner, route finder, and game relation database
Discworld is composed of two core components: **Twoflower** and **Mapp**.

**Twoflower** is the core component: it exposes a generic game relation database
(GameDB) and implements a goal planner (using a depth-first search) and route
finder (using A\*). The GameDB could be used to map relationships, such as the
XP rewarded for an action, the resources required to make an item, and so on.
You're really limited only by how well you can model these relationships in a
graph.

**Mapp** is an extension of **Twoflower** modeling *IttleScape*, a WIP game
inspired by *RuneScape* by Jagex. Only high-level things like shops are
exposed currently.

**Glooper** is a C wrapper over **Twoflower** and **Mapp**. (There's a pun
there: glooper, glue-per, glue--Glooper glues Twoflower via FFI. Ok.)

**Rincewind** is a tool written in C# will allow editing of the GameDB. It will
use **Glooper** to call **Twoflower**. There may be functionality explicitly
for *IttleScape*, but it will work with any GameDB. **Rincewind** also includes
a managed implementation of Mapp.

Currently, **Twoflower** and **Mapp** are under heavy refactoring from being
used in a failed proof-of-concept called *AUTONOMAUS*.

## Copyright & License

Copyright Aaron Bolyard aka [bk]door.maus

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.