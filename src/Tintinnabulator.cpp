//
// Created by jamiebatten on 1/23/24.
//

#include <iostream>
#include "Tintinnabulator.h"

Tintinnabulator::Tintinnabulator(){
    std::cout << "Tintinnabulator CREATED" << std::endl;
}

Tintinnabulator::~Tintinnabulator(){
    std::cout << "Tintinnabulator DESTROYED" << std::endl;
}

juce::MidiMessage Tintinnabulator::GenerateTVoice(juce::MidiMessage msg) {

    // WE NEED TO WORK OUT BASED ON THE TINTINABULATOR NOTES WHICH NOTE TO GENERATE IN THE T VOICE.

    int midiNote = msg.getNoteNumber() + 4; // Harmonizing with original note
    float velocity = 0.6f; // Set desired velocity for harmony note

    // Create the note on message and add it to the processed MIDI buffer
    return juce::MidiMessage::noteOn(1, midiNote, velocity);
}

juce::MidiMessage Tintinnabulator::RemoveTVoice(juce::MidiMessage msg) {
    // REMOVE MAJOR THIRD
    int midiNote = msg.getNoteNumber() + 4; // Corresponding harmonized note

    // Create the note off message and add it to the processed MIDI buffer
    return juce::MidiMessage::noteOff(1, midiNote);
}

