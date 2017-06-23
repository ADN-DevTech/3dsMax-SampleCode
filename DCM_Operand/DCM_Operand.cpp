//**************************************************************************/
// Copyright (c) 1998-2017 Autodesk, Inc.
// All rights reserved.
// 
//**************************************************************************/
// DESCRIPTION: Example Data Channel Modifier Engine
// Based on the Clamp Engine
// NOTE - the terms "engine" and "operator" are used interchangeably.  
// "Engine" tends to be used in the SDK and "operator" in the max UI.
// AUTHOR: Drew Avis
//***************************************************************************/

#include "DCM_Operand.h"
#include "IMNMeshDataChannel.h"
#include "mnmesh.h"
#include "mnmath.h"
#include "Qt_Sample_Rollup.h"


using namespace MaxSDK::ChannelData; // This is where IDataChannelEngine lives


#define SDKEngineSample_CLASS_ID	Class_ID(0x9504b028, 0x5deb136d)
#define PBLOCK_REF	0

class SDKEngineSample : public IDataChannelEngine
{
public:
	// parameter blocks
	enum { kParameters };
	// 
	enum
	{
		pbClamp_Min,
		pbClamp_Max
	};

	//Constructor/Destructor
	SDKEngineSample();
	~SDKEngineSample();

	//From Animatable
	virtual Class_ID ClassID() { return SDKEngineSample_CLASS_ID; }
	virtual SClass_ID SuperClassID() { return OSM_CLASS_ID; }
	// ReferenceMaker
	virtual RefResult NotifyRefChanged(const Interval& changeInt, RefTargetHandle hTarget, PartID& partID, RefMessage message, BOOL propagate);

	// ReferenceTarget
	virtual int	NumParamBlocks() { return 1; }					// return number of ParamBlocks in this instance
	virtual IParamBlock2* GetParamBlock(int /*i*/) { return pblock; } // return i'th ParamBlock
	virtual IParamBlock2* GetParamBlockByID(BlockID id) { return (pblock->ID() == id) ? pblock : NULL; } // return id'd ParamBlock
	virtual int NumRefs() { return 1; }
	virtual RefTargetHandle GetReference(int i);
	virtual int NumSubs() { return 1; }
	virtual Animatable* SubAnim(int /*i*/) { return pblock; }
	virtual TSTR SubAnimName(int /*i*/) { return GetString(IDS_PARAMS); }

	Interface_ID	GetID() { return DATACHANNELENGINE_INTERFACE; }
	BaseInterface* GetInterface(Interface_ID id)
	{
		if (id == DATACHANNELENGINE_INTERFACE)
			return static_cast<IDataChannelEngine *>(this);
		else
			return ReferenceTarget::GetInterface(id);
	}

	

	// IDataChannelEngine							
	virtual void GetUIName(TSTR& name);
	virtual void GetTooltip(TSTR& name);

	virtual MaxSDK::Array<InputDataType> InputRequirements();
	virtual MaxSDK::Array<OutputDataType> OutputRequirements();
	virtual MaxSDK::Array<ChannelType> OutputChannelTypes();
	virtual IndexChannel IndexChannelToBeUsed();
	virtual void InputType(IOutputData /*data*/);
	virtual Interval Process(TimeValue t, MaxSDK::Array<IInputData>& inData, MaxSDK::Array<IOutputData>& outData, int& tempPerInstanceData, PartID& channelsChanged);

	virtual void BeginEditParams(IObjParam  *ip, ULONG flags, Animatable *prev);
	virtual void EndEditParams(IObjParam *ip, ULONG flags, Animatable *next);
	virtual RefTargetHandle Clone(RemapDir& remap);

protected:
	virtual void SetReference(int , RefTargetHandle rtarg);

private:
	// Parameter block
	IParamBlock2 *pblock; //ref 0

	// An array of data types we can handle, populated in the constructor.
	// Can contain up to 3 types
	MaxSDK::Array<InputDataType> mInputs;  
	MaxSDK::Array<OutputDataType> mOutputs;
	MaxSDK::Array<ChannelType> mOutputsChannelTypes;
	IndexChannel mIndexChannel;
};

void SDKEngineSample::SetReference( int i, RefTargetHandle rtarg )
{
	if (i == PBLOCK_REF)
	{
		pblock=(IParamBlock2*)rtarg;
	}
}

RefTargetHandle SDKEngineSample::GetReference( int i)
{
	if (i == PBLOCK_REF)
	{
		return pblock;
	}
	return nullptr;
}

// This is the name that shows up in the DCM UI
void SDKEngineSample::GetUIName(TSTR& name)
{
	name.printf(_T("%s"), GetString(IDS_UINAME));
}

// Tooltip for the engine in the DCM UI
void SDKEngineSample::GetTooltip(TSTR& name)
{
	name.printf(_T("%s"), GetString(IDS_TOOLTIP));
}

// Returns what the engine needs for data
MaxSDK::Array<InputDataType> SDKEngineSample::InputRequirements()
{
	return mInputs;
}

// What the engine outputs
MaxSDK::Array<OutputDataType> SDKEngineSample::OutputRequirements()
{
	return mOutputs;
}

// Called before you process your data.  It passes in the data description
// of what's flowing into your process method.  You can query the data
// type to change how you process the data.
void SDKEngineSample::InputType(IOutputData data)
{
	mOutputs[0] = data.GetType();
	mIndexChannel = data.GetIndexChannel();
}


IndexChannel SDKEngineSample::IndexChannelToBeUsed()
{
	return mIndexChannel;
}


MaxSDK::Array<ChannelType> SDKEngineSample::OutputChannelTypes()
{
	return mOutputsChannelTypes;
}



class SDKEngineSampleClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return FALSE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new SDKEngineSample(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return DATACHANNELENGINE_SUPER_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return SDKEngineSample_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("SDKEngineSample"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	bool			UseOnlyInternalNameForMAXScriptExposure() { return true; }

	virtual MaxSDK::QMaxParamBlockWidget* CreateQtWidget(
		ReferenceMaker& /*owner*/,
		IParamBlock2& paramBlock,
		const MapID /*paramMapID*/,
		MSTR& rollupTitle,
		int& /*rollupFlags*/,
		int& /*rollupCategory*/)
	{

		if (paramBlock.ID() == SDKEngineSample::kParameters)
		{
			// this invokes the Qt translation system:
			//: this is a comment for the translation team 
			rollupTitle = Qt_Sample_Rollup::tr("Clamp");
			return new Qt_Sample_Rollup();
		}
		return nullptr;

	};

};


ClassDesc2* GetSDKEngineSampleDesc() { 
	static SDKEngineSampleClassDesc SDKEngineSampleDesc;
	return &SDKEngineSampleDesc; 
}




enum { sdkenginesample_params };

static ParamBlockDesc2 sdkenginesample_param_blk ( sdkenginesample_params, _T("OperandSample Rollup"),  0, GetSDKEngineSampleDesc(), 
	P_AUTO_CONSTRUCT + P_AUTO_UI_QT, PBLOCK_REF, 
	// params
	SDKEngineSample::pbClamp_Min, _T("clampMin"), TYPE_FLOAT, P_RESET_DEFAULT | P_ANIMATABLE, IDS_MIN,
	p_default, -5000.0f,
	p_range, -100000.0f, 100000.0f,
	p_end,

	SDKEngineSample::pbClamp_Max, _T("clampMax"), TYPE_FLOAT, P_RESET_DEFAULT | P_ANIMATABLE, IDS_MAX,
	p_default, 5000.0f,
	p_range, -100000.0f, 100000.0f,
	p_end,
	p_end
	);




//--- SDKEngineSample -------------------------------------------------------
SDKEngineSample::SDKEngineSample()
	: pblock(nullptr)
{
	GetSDKEngineSampleDesc()->MakeAutoParamBlocks(this);

	// If you are an input operator (you only create data), you would have an mInputs with length 0.
	// If you are an output operator, you would have an mOutputs with length 0.
	// In this case we are a process operator, so we define both.

	// Set up inputs that we accept
	mInputs.setLengthUsed(3);
	// INode that owns the stack geometry - add this if you need the world space, for example for influence or velocity over time
	// We don't really need this for this example, but it has no overhead.
	mInputs[0] = InputDataType::kType_INode; 
	// MNMesh in the stack - add this if you need mesh data, for example to do a blur.  Note, you should not change the MNMesh data,
	// such as the topology, as this will cause the stack to get out of sync.
	mInputs[1] = InputDataType::kType_MNMesh; 
	// Output of the previous engine in the DCM stack.  Most operand engines only need this data type.
	mInputs[2] = InputDataType::kType_Stack_Input; 

	mOutputs.setLengthUsed(1);
	// The output data type.  The first entry in the array mOutputs[0] is special as it connects to the stack.  
	// You can use other entries in the array to store data (for example skin weights), as it is not deleted and persists in the scene.
	mOutputs[0] = OutputDataType::kType_FloatArray;  

	// Specifies the output data type, which determines what kind of engine can be placed under this one in the stack.
	// In this case we don't care, so we can output to any engine.
	mOutputsChannelTypes.setLengthUsed(1);
	mOutputsChannelTypes[0] = ChannelType::kChannel_DoesNotCare; 

	// Only use if you need to specify a vertex channel, for example if you're working on position or map channels.
	mIndexChannel = IndexChannel::kIndexChannel_None;  // Not associated with any face indices
}

SDKEngineSample::~SDKEngineSample()
{
}

void SDKEngineSample::BeginEditParams( IObjParam* ip, ULONG flags, Animatable* prev )
{
	TimeValue t = ip->GetTime();
	NotifyDependents(Interval(t,t), PART_ALL, REFMSG_BEGIN_EDIT);
	NotifyDependents(Interval(t,t), PART_ALL, REFMSG_MOD_DISPLAY_ON);
	SetAFlag(A_MOD_BEING_EDITED);	

	GetSDKEngineSampleDesc()->BeginEditParams(ip, this, flags, prev);
}

void SDKEngineSample::EndEditParams( IObjParam *ip, ULONG flags, Animatable *next)
{
	GetSDKEngineSampleDesc()->EndEditParams(ip, this, flags, next);

	TimeValue t = ip->GetTime();
	ClearAFlag(A_MOD_BEING_EDITED);
	NotifyDependents(Interval(t,t), PART_ALL, REFMSG_END_EDIT);
	NotifyDependents(Interval(t,t), PART_ALL, REFMSG_MOD_DISPLAY_OFF);
}

RefTargetHandle SDKEngineSample::Clone(RemapDir & remap)
{
	SDKEngineSample *mod = new SDKEngineSample();
	mod->ReplaceReference(PBLOCK_REF, remap.CloneRef(pblock));
	BaseClone(this, mod, remap);
	return mod;
}


//From ReferenceMaker 
RefResult SDKEngineSample::NotifyRefChanged(
		const Interval& /*changeInt*/, RefTargetHandle hTarget,
		PartID& /*partID*/,  RefMessage message, BOOL /*propagate*/) 
{
	if ((hTarget == pblock))
	{
		ParamID changing_param = pblock->LastNotifyParamID();
		sdkenginesample_param_blk.InvalidateUI(changing_param);
	}
	return REF_SUCCEED;
}

// This is where all the work is done
// Process the inData and fill out the outData
Interval SDKEngineSample::Process(TimeValue t, MaxSDK::Array<IInputData>& inData, MaxSDK::Array<IOutputData>& outData, int & tempPerInstanceData, PartID & channelsChanged)
{
	// validate the incoming data
	// The inData array matches what we specified in inputRequirements()
	if (inData[0].GetType() != InputDataType::kType_INode)
		return FOREVER;
	if (inData[1].GetType() != InputDataType::kType_MNMesh)
		return FOREVER;
	if (inData[2].GetType() != InputDataType::kType_Stack_Input)
		return FOREVER;

	Interval iv = FOREVER;
	float minValue = 1.0f;
	float maxValue = 1.0f;
	pblock->GetValue(pbClamp_Min, t, minValue, iv);
	pblock->GetValue(pbClamp_Max, t, maxValue, iv);
	IInputData iData = inData[2];

	// This should always be present, we don't need to look at inData[0] or inData[1]
	if (iData.GetType() == InputDataType::kType_Stack_Input)
	{
		// This Engine can adapt the process depending on the type of data flowing into it.
		// In this case, we check whether it's a float, int, point3 or matrix3 and process 
		// accordingly.
		IOutputData* data = (IOutputData*)iData.Get();
		if (data->GetType() == OutputDataType::kType_FloatArray)
		{
			MaxSDK::Array<float>& od = *(MaxSDK::Array<float>*) outData[0].Get();
			MaxSDK::Array<float>& id = *(MaxSDK::Array<float>*) data->Get();
			if (od.lengthUsed() != id.lengthUsed())
				od.setLengthUsed(id.lengthUsed());

			for (int i = 0; i < od.lengthUsed(); i++)
			{
				if (id[i] < minValue)
					od[i] = minValue;
				else if (id[i] > maxValue)
					od[i] = maxValue;
				else
					od[i] = id[i];
			}
		}
		else if (data->GetType() == OutputDataType::kType_IntArray)
		{
			MaxSDK::Array<int>& od = *(MaxSDK::Array<int>*) outData[0].Get();
			MaxSDK::Array<int>& id = *(MaxSDK::Array<int>*) data->Get();
			if (od.lengthUsed() != id.lengthUsed())
				od.setLengthUsed(id.lengthUsed());

			for (int i = 0; i < od.lengthUsed(); i++)
			{
				if (id[i] < minValue)
					od[i] = minValue;
				else if (id[i] > maxValue)
					od[i] = maxValue;
				else
					od[i] = id[i];
			}
		}
		else if (data->GetType() == OutputDataType::kType_Point3Array)
		{
			MaxSDK::Array<Point3>& od = *(MaxSDK::Array<Point3>*) outData[0].Get();
			MaxSDK::Array<Point3>& id = *(MaxSDK::Array<Point3>*) data->Get();
			if (od.lengthUsed() != id.lengthUsed())
				od.setLengthUsed(id.lengthUsed());

			for (int i = 0; i < od.lengthUsed(); i++)
			{
				float d = Length(id[i]);
				Point3 n = Normalize(id[i]);
				if (d < minValue)
					od[i] = n * minValue;
				else if (d > maxValue)
					od[i] = n * maxValue;
				else
					od[i] = id[i];

			}
		}
		else if (data->GetType() == OutputDataType::kType_Matrix3Array)
		{
			MaxSDK::Array<Matrix3>& od = *(MaxSDK::Array<Matrix3>*) outData[0].Get();
			MaxSDK::Array<Matrix3>& id = *(MaxSDK::Array<Matrix3>*) data->Get();
			if (od.lengthUsed() != id.lengthUsed())
				od.setLengthUsed(id.lengthUsed());
			for (int i = 0; i < od.lengthUsed(); i++)
			{
				od[i] = id[i];
			}
		}

		outData[0].SetChannels(data->GetChannels());
	}
	return iv;
}

