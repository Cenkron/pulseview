/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
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

#ifndef PULSEVIEW_PV_DATA_DECODER_H
#define PULSEVIEW_PV_DATA_DECODER_H

#include "signaldata.h"

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <QObject>

struct srd_decoder;
struct srd_decoder_inst;
struct srd_probe;

namespace pv {

namespace view {
class Signal;

namespace decode {
class Annotation;
}

}

namespace data {

class Logic;

class Decoder : public QObject, public SignalData
{
	Q_OBJECT

private:
	static const double DecodeMargin;
	static const double DecodeThreshold;
	static const int64_t DecodeChunkLength;

public:
	Decoder(const srd_decoder *const decoder,
		std::map<const srd_probe*,
			boost::shared_ptr<pv::view::Signal> > probes,
		GHashTable *options);

	virtual ~Decoder();

	const srd_decoder* get_decoder() const;

	const std::vector< boost::shared_ptr<pv::view::decode::Annotation> >
		annotations() const;

	void clear_snapshots();

private:
	void begin_decode();

	void init_decoder();

	void decode_proc(boost::shared_ptr<data::Logic> data);

	static void annotation_callback(srd_proto_data *pdata,
		void *decoder);

private:
	const srd_decoder *const _decoder;
	std::map<const srd_probe*, boost::shared_ptr<view::Signal> >
		_probes;
	GHashTable *_options;

	srd_decoder_inst *_decoder_inst;

	mutable boost::mutex _annotations_mutex;
	std::vector< boost::shared_ptr<pv::view::decode::Annotation> >
		_annotations;

	boost::thread _decode_thread;
};

} // namespace data
} // namespace pv

#endif // PULSEVIEW_PV_DATA_DECODER_H
