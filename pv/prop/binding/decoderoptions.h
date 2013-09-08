/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef PULSEVIEW_PV_PROP_BINDING_DECODEROPTIONS_H
#define PULSEVIEW_PV_PROP_BINDING_DECODEROPTIONS_H

#include <libsigrokdecode/libsigrokdecode.h>

#include "binding.h"

namespace pv {
namespace prop {
namespace binding {

class DecoderOptions : public Binding
{
public:
	DecoderOptions(const srd_decoder *decoder, GHashTable *options);

private:
	GVariant* getter(const char *id);

	void setter(const char *id, GVariant *value);

private:
	const srd_decoder *const _decoder;
	GHashTable *const _options;
};

} // binding
} // prop
} // pv

#endif // PULSEVIEW_PV_PROP_BINDING_DECODEROPTIONS_H