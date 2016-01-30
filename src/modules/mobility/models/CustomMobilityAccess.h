//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


#ifndef CUSTOM_MOBILITY_ACCESS_H
#define CUSTOM_MOBILITY_ACCESS_H

#include "INETDefs.h"

#include "ModuleAccess.h"
#include "CustomRectangleMobility.h"
#include "CustomLinearMobility.h"


/**
 * Gives access to the IMobility submodule.
 */
class INET_API CustomMobilityAccess : public ModuleAccess<CustomLinearMobility>
{
    public:
        //CustomMobilityAccess() : ModuleAccess<CustomRectangleMobility>("mobility") {}
    CustomMobilityAccess() : ModuleAccess<CustomLinearMobility>("mobility") {}
};

#endif
