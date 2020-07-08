#include "LFOParametersView.h"
LFOParametersView::LFOParametersView(LFOParameters* params)
    : parameters(params)
{

    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText(parameters->getName(), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(knobsView);

    setWantsKeyboardFocus(true);

}

void LFOParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void LFOParametersView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);
    juce::Rectangle<int> knobsBounds(0, getHeight() / 4, getWidth(), getHeight() / 2);
    knobsView.setBounds(knobsBounds);

}

void LFOParametersView::currentPresetLFOParametersChanged(LFOParameters* params)
{

    parameters = params;
    titleLabel.setText(parameters->getName(), juce::dontSendNotification);
    repaint();

}