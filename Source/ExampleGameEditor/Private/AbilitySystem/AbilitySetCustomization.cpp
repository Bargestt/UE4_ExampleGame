// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySetCustomization.h"
#include "AbilitySet.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "SButton.h"

#define LOCTEXT_NAMESPACE "ExampleGameEditorModule"


// Note hiding is done using the DetailBuilder, not the CategoryBuilder
//DetailBuilder.HideProperty(Property);

// Hide an entire category
//DetailBuilder.HideCategory(TEXT("CategoryName"));

// Add a property to a category (properties will be shown in the order you add them)
//Category.AddProperty(Property);


TSharedRef< IDetailCustomization > FAbilitySetCustomization::MakeInstance()
{
	return MakeShareable(new FAbilitySetCustomization());
}


void FAbilitySetCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//Lambdas

	auto AddNew = []
	{
		return FReply::Handled();
	};




	TSharedRef< IPropertyHandle > PropABilityTypes = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAbilitySet, ABilityTypes));
	TSharedRef< IPropertyHandle > PropAbilities = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAbilitySet, Abilities));

	IDetailCategoryBuilder& TypesCategory = DetailBuilder.EditCategory(TEXT("Types"));


	TArray< TWeakObjectPtr< UObject > > Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() != 1)
	{
		return;
	}

	TWeakObjectPtr<UAbilitySet> MyObject = Cast< UAbilitySet >(Objects[0].Get());

	TypesCategory.AddCustomRow(LOCTEXT("TypesCategory", "Types"))
		.WholeRowContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TypesCategoryText", "Here are available classes\n"))
		];
	

	if (PropABilityTypes->IsValidHandle())
	{
		TypesCategory.AddProperty(PropABilityTypes);
	}

	TypesCategory.AddCustomRow(LOCTEXT("TypesCategory", "ButtonAdd"))
		.NameContent().MinDesiredWidth(300)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Extra info", "Custom row header name"))
		]
		.ValueContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(LOCTEXT("ButtonAdd", "AddNew"))
					.OnClicked_Lambda(AddNew)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Text", "   Moar text"))
				]
			];
}


#undef LOCTEXT_NAMESPACE