#include "EditView.h"
#include "CommandList.h"
EditView::EditView(tracktion_engine::Edit& e, juce::ApplicationCommandManager& cm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      commandManager(cm),
      tracksView(std::make_unique<TracksView>(cm)),
      instrumentListView(std::make_unique<InstrumentListView>(e.engine.getPluginManager(), e.engine.getTemporaryFileManager(), cm))
{

    addTab(tracksTabName, juce::Colours::transparentBlack, tracksView.get(), true);
    addTab(instrumentListTabName, juce::Colours::transparentBlack, instrumentListView.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());

    // Set tracks as initial view
    juce::StringArray names = getTabNames();
    int tracksIndex = names.indexOf(tracksTabName);
    setCurrentTabIndex(tracksIndex);


}

void EditView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void EditView::resized()
{

    juce::TabbedComponent::resized();
    tracksView->setBounds(getLocalBounds());
    instrumentListView->setBounds(getLocalBounds());

}

juce::ApplicationCommandTarget* EditView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void EditView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::SHOW_TRACKS);
    commands.add(AppCommands::SHOW_INSTRUMENT_LIST);
}

void EditView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {
        case SHOW_TRACKS:
            result.setInfo("Show Tracks", "Display the tracks screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::homeKey, 0);
            break;

        case SHOW_INSTRUMENT_LIST:
            result.setInfo("Show ADSR Parameters", "Display the adsr parameters screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::pageUpKey, 0);
            break;

        default:
            break;
    }


}

bool EditView::perform (const InvocationInfo &info)
{

    juce::StringArray names = getTabNames();

    switch(info.commandID) {


        case SHOW_TRACKS:
        {

            int tracksIndex = names.indexOf(tracksTabName);
            setCurrentTabIndex(tracksIndex);
            break;

        }

        case SHOW_INSTRUMENT_LIST:
        {

            int instrumentListIndex = names.indexOf(instrumentListTabName);
            setCurrentTabIndex(instrumentListIndex);
            break;

        }

        default:
            return false;
    }

    return true;

}
