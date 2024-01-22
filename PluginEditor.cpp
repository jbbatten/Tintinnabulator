#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p) {
    juce::ignoreUnused(processorRef);

    // Initialize ui

    firstPositionInferiorButton.setButtonText("First Position Inferior");
    secondPositionInferiorButton.setButtonText("Second Position Inferior");
    firstPositionSuperiorButton.setButtonText("First Position Superior");
    secondPositionSuperiorButton.setButtonText("Second Position Superior");

    firstPositionInferiorButton.addListener(this);
    secondPositionInferiorButton.addListener(this);
    firstPositionSuperiorButton.addListener(this);
    secondPositionSuperiorButton.addListener(this);

    notePickerOne.addItemList(notes, 0);
    notePickerTwo.addItemList(notes, 0);
    notePickerThree.addItemList(notes, 0);

    // SET TO A
    notePickerOne.setSelectedId(1);
    // SET TO C
    notePickerTwo.setSelectedId(4);
    // SET TO E
    notePickerThree.setSelectedId(8);

    notePickerOne.addListener(this);
    notePickerTwo.addListener(this);
    notePickerThree.addListener(this);

    addAndMakeVisible(notePickerOne);
    addAndMakeVisible(notePickerTwo);
    addAndMakeVisible(notePickerThree);

    addAndMakeVisible(firstPositionInferiorButton);
    addAndMakeVisible(secondPositionInferiorButton);
    addAndMakeVisible(firstPositionSuperiorButton);
    addAndMakeVisible(secondPositionSuperiorButton);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

void AudioPluginAudioProcessorEditor::resized() {
    notePickerOne.setBounds(10, 10, 70, 30); // x, y, width, height in pixels
    notePickerTwo.setBounds(90, 10, 70, 30); // x, y, width, height in pixels
    notePickerThree.setBounds(170, 10, 70, 30); // x, y, width, height in pixels

    firstPositionInferiorButton.setBounds(10, 50, 150, 30);
    secondPositionInferiorButton.setBounds(10, 100, 150, 30);
    firstPositionSuperiorButton.setBounds(10, 150, 150, 30);
    secondPositionSuperiorButton.setBounds(10, 200, 150, 30);
}

void AudioPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) {
    if (comboBoxThatHasChanged == &notePickerOne) {
        int selectedItemId = notePickerOne.getSelectedId();
        processorRef.noteOne = notePickerOne.getItemText(selectedItemId);
        DBG(processorRef.noteOne);
    }
    if (comboBoxThatHasChanged == &notePickerTwo) {
        int selectedItemId = notePickerTwo.getSelectedId();
        processorRef.noteTwo = notePickerTwo.getItemText(selectedItemId);
        DBG(processorRef.noteTwo);
    }
    if (comboBoxThatHasChanged == &notePickerThree) {
        int selectedItemId = notePickerThree.getSelectedId();
        processorRef.noteThree = notePickerThree.getItemText(selectedItemId);
        DBG(processorRef.noteThree);
    }
}

void AudioPluginAudioProcessorEditor::buttonClicked(juce::Button *button) {

    // Deselect all buttons
    firstPositionInferiorButton.setToggleState(false, juce::dontSendNotification);
    secondPositionInferiorButton.setToggleState(false, juce::dontSendNotification);
    firstPositionSuperiorButton.setToggleState(false, juce::dontSendNotification);
    secondPositionSuperiorButton.setToggleState(false, juce::dontSendNotification);

    // Select the clicked button
    button->setToggleState(true, juce::dontSendNotification);

    // Here, you can handle the logic for each button
    if (button == &firstPositionInferiorButton) {
        // Handle Logic
    } else if (button == &secondPositionInferiorButton) {
        // Handle Logic
    } else if (button == &firstPositionSuperiorButton) {
        // Handle Logic
    } else if (button == &secondPositionSuperiorButton) {
        // Handle Logic
    }
}
