#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final
        : public juce::AudioProcessorEditor,
          private juce::ComboBox::Listener,
          private juce::Button::Listener {
public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);

    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;


    void resized() override;

private:
    juce::ComboBox notePickerOne;
    juce::ComboBox notePickerTwo;
    juce::ComboBox notePickerThree;

    juce::TextButton firstPositionInferiorButton;
    juce::TextButton secondPositionInferiorButton;
    juce::TextButton firstPositionSuperiorButton;
    juce::TextButton secondPositionSuperiorButton;

    void buttonClicked(juce::Button *button) override;

    const juce::StringArray notes = {"A", "Bb", "B", "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#"};

    // Override the comboBoxChanged method
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor &processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
