#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
        : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                                 .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                                 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
) {
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram() {
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index, const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages) {
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto *channelData = buffer.getWritePointer(channel);
        juce::ignoreUnused(channelData);
        // ..do something to the data...
    }

    processMidiBuffer(buffer, midiMessages);
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
    return new AudioPluginAudioProcessorEditor(*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused(data, sizeInBytes);
}

void AudioPluginAudioProcessor::processMidiBuffer(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiBuffer) {

    juce::MidiBuffer processedMidi;
    constexpr std::size_t midiChannel = 1;
    int sampleNumber; // Sample number for each MIDI message

    // Iterate through each MIDI event in the buffer
    for (const auto &meta: midiBuffer) {
        const auto msg = meta.getMessage();
        sampleNumber = meta.samplePosition; // Set the current sample number

        DBG("Note Number: " + (juce::String) msg.getNoteNumber());
        DBG("Velocity: " + (juce::String) msg.getVelocity());

        // Check for Note On event
        if (msg.isNoteOn()) {

            // ADD A MAJOR THIRD
            int midiNote = msg.getNoteNumber() + 4; // Harmonizing with original note
            float velocity = 0.6f; // Set desired velocity for harmony note

            // Create the note on message and add it to the processed MIDI buffer
            juce::MidiMessage noteOn = juce::MidiMessage::noteOn(midiChannel, midiNote, velocity);
            processedMidi.addEvent(noteOn, sampleNumber);

            // ADD A FIFTH
            midiNote = msg.getNoteNumber() + 7; // Harmonizing with original note
            velocity = 0.6f;

            // Create the note on message and add it to the processed MIDI buffer
            noteOn = juce::MidiMessage::noteOn(midiChannel, midiNote, velocity);
            processedMidi.addEvent(noteOn, sampleNumber);
        }
            // Check for Note Off event or Note On with zero velocity
        else if (msg.isNoteOff() || (msg.isNoteOn() && msg.getVelocity() == 0)) {

            // REMOVE MAJOR THIRD
            int midiNote = msg.getNoteNumber() + 4; // Corresponding harmonized note

            // Create the note off message and add it to the processed MIDI buffer
            juce::MidiMessage noteOff = juce::MidiMessage::noteOff(midiChannel, midiNote);
            processedMidi.addEvent(noteOff, sampleNumber);

            // REMOVE FIFTH
            midiNote = msg.getNoteNumber() + 7; // Corresponding harmonized note

            // Create the note off message and add it to the processed MIDI buffer
            noteOff = juce::MidiMessage::noteOff(midiChannel, midiNote);
            processedMidi.addEvent(noteOff, sampleNumber);
        }
    }

    // Merge the processed MIDI messages with the incoming MIDI messages
    midiBuffer.addEvents(processedMidi, 0, buffer.getNumSamples(), 0);
}

void AudioPluginAudioProcessor::handleComboBoxChange(int selectedItemId) {

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new AudioPluginAudioProcessor();
}
