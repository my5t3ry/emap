/*
 *  Copyright 2013 Bill Brown
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * FSynth.h
 *
 *  Created on: Apr 28, 2013
 *      Author: bill
 */

#ifndef FLUIDSYNTH_H_
#define FLUIDSYNTH_H_

#include <fluidsynth.h>


class FSynth {

public:

	FSynth(double sample_rate);
	~FSynth();

	fluid_synth_t* get_synth();

	fluid_settings_t* get_settings();

	fluid_sfont_t* get_soundfont();

	void set_soundfont(fluid_sfont_t* soundfont);

protected:

	//set up the midi driver
	fluid_settings_t* settings;

	fluid_midi_driver_t* mdriver;

	fluid_synth_t* synth;

	fluid_audio_driver_t* adriver;

	fluid_sfont_t* soundfont; //the loaded soundfont

};

int handle_midi_event(void* data, fluid_midi_event_t* event);

#endif /* FLUIDSYNTH_H_ */
