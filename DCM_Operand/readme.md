# Readme: Data Channel Modifier Engine Sample

This example illustrates how to create a new Data Channel Modifier engine for 3ds Max.
You can use it as a template to create new engines.  

**Note:** the 3ds Max SDK Plugin Wizard does not yet support DCM Engines as a new new project type,
so the best current approach is to copy this project.

## Requirements:

* 3ds Max 2018
* Visual Studio 2015 with the Qt VS Tools extension
* Qt 5.6.2

This project uses Qt for the DCM Engine's UI.  See [this tutorial](http://area.autodesk.com/learning/series/undefined/setting-up-a-3ds-max-2018-plug-in-project-to-use-qt) 
for an overview on how to set up a new project that uses Qt.

## Overview:

To create a new DCM Engine, you derive from the `IDataChannelEngine` class.  The output type is .dlm (the
same as other modifiers), and when placed in <3dsmax>\Plugins\, the plug-in is loaded at startup, and available in the 
DCM Operator list.

There are three flavors of engine (or "operator" as they are called in the Max UI):
* Input engines, which take a mesh or node as input, and select one of the channels to put onto the stack
* Process engines, which take an input channel, operate on it, and then put the data back into an output channel
* Output engines, which take an input channel, then put the data back to a mesh or node.

This sample implements an Process engine, based on the current `Clamp` engine.
