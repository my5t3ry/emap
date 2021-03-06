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
 * FSynth.cc
 *
 *  Created on: Apr 28, 2013
 *      Author: bill
 */

#include <fluidsynth.h>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <types.h>
#include <stdlib.h>

#include "fsynth.h"

FSynth::FSynth(double sample_rate) {

	std::cout << "making EMAP synth (fluidsynth wrapper)" << std::endl;

	settings = new_fluid_settings();

	fluid_settings_setstr(settings, "audio.jack.id", "EMAP");

	fluid_settings_setstr(settings, "midi.jack.id", "EMAP");

	fluid_settings_setstr(settings, "midi.alsa_seq.id", "EMAP");

	synth = new_fluid_synth(settings);
	
	mdriver = new_fluid_midi_driver(settings, handle_midi_event,
				(void*) synth);

	std::cout << "made FSynth midi driver" << std::endl;

	adriver = new_fluid_audio_driver(settings, synth);

	std::cout << "made FSynth audio driver" << std::endl;
}

FSynth::~FSynth() {

}

int handle_midi_event(void* data, fluid_midi_event_t* event) {

	//try {

	fluid_synth_t* synth = (fluid_synth_t*) data;

	int event_type = fluid_midi_event_get_type(event);

	//int type = fluid_midi_event_get_type(event);
	int channel = fluid_midi_event_get_channel(event);
	int key = fluid_midi_event_get_key(event);
	int velocity = fluid_midi_event_get_velocity(event);
	int control = fluid_midi_event_get_control(event);
	int value = fluid_midi_event_get_value(event);
	int program = fluid_midi_event_get_program(event);
	int pitch = fluid_midi_event_get_pitch(event);
	/* Play a note */

	switch (event_type) {
	case 0x80: //NOTE_OFF:
		//std::cout << "NOTE_OFF: " << std::endl;
		fluid_synth_noteoff(synth, channel, key);
		break;
	case 0x90: //NOTE_ON
		//std::cout << "NOTE_ON: " << std::endl;
		fluid_synth_noteon(synth, channel, key, velocity);
		break;
	case 0xa0: //KEY_PRESSURE
		//std::cout << "KEY_PRESSURE / Aftertouch" << std::endl;
		break;
	case 0xb0: //CONTROL_CHANGE
		//std::cout << "CONTROL_CHANGE" << std::endl;
		fluid_synth_cc(synth, channel, control, value);
		break;
	case 0xc0: //PROGRAM_CHANGE
		//std::cout << "PROGRAM_CHANGE" << std::endl;
		fluid_synth_program_change(synth, channel, program);
		break;
	case 0xd0: //CHANNEL_PRESSURE
		//std::cout << "CHANNEL_PRESSURE" << std::endl;
		//fluid_synth_set_gain(synth, velocity);
		fluid_synth_channel_pressure(synth, channel, value);
		break;
	case 0xe0: //PITCH_BEND
		//std::cout << "PITCH_BEND" << std::endl;
		fluid_synth_pitch_bend(synth, channel, pitch);
		break;

	default:
		std::cout << "Undetected event" << std::endl;
		break;
	};

	return 0;
}

fluid_synth_t* FSynth::get_synth() {
	return synth;
}

fluid_settings_t* FSynth::get_settings() {
	return settings;
}

fluid_sfont_t* FSynth::get_soundfont() {
	return soundfont;
}

void FSynth::set_soundfont(fluid_sfont_t* soundfont) {
	this->soundfont = soundfont;
}
