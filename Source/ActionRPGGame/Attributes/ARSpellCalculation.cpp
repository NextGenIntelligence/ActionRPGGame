// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ActionRPGGame.h"
#include "GAAttributeComponent.h"
#include "GAAttributesBase.h"
#include "GAEffects.h"
#include "ARCharacterAttributes.h"
#include "ARSpellCalculation.h"

UARSpellCalculation::UARSpellCalculation(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}
FGAAttributeData UARSpellCalculation::OutgoingModifyEffect(const FGAAttributeData& DataIn)
{
	FGAAttributeData data = DataIn;
	return data;
}
FGAAttributeData UARSpellCalculation::IncomingModifyEffect(const FGAAttributeData& DataIn)
{
	FGAAttributeData data = DataIn;
	UARCharacterAttributes* InstAttr = Cast<UARCharacterAttributes>(DataIn.Context.InstigatorComp->DefaultAttributes);
	UARCharacterAttributes* TargAttr = Cast<UARCharacterAttributes>(DataIn.Context.TargetComp->DefaultAttributes);
	//UProperty* ModifiedProperty = FindFieldChecked<UProperty>(UARCharacterAttributes::StaticClass(), data.Attribute.AttributeName);

	FGAModifierStack OffStack = DataIn.Context.InstigatorComp->ActiveEffects.ModifierContainer.GetOutgoingModifierStack(DataIn);
	FGAModifierStack DefStack = DataIn.Context.TargetComp->ActiveEffects.ModifierContainer.GetIncomingModifierStack(DataIn);
	//
	
	data.Value = data.Value + OffStack.Additive;
	data.Value = data.Value - OffStack.Subtractive;

	data.Value = data.Value + (data.Value * OffStack.Multiply);
	data.Value = data.Value - (data.Value * OffStack.Divide);

	//so additive bonus in defense would work like penalty and increas damage received ?
	data.Value = data.Value + DefStack.Additive;
	data.Value = data.Value - DefStack.Subtractive;

	data.Value = data.Value + (data.Value * DefStack.Multiply);
	data.Value = data.Value - (data.Value * DefStack.Divide);
	
	return data;
}