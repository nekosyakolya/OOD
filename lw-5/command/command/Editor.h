#pragma once
#include "IDocument.h"
#include <functional>

class CEditor
{
public:
	CEditor();
	void Run();
	~CEditor();

private:
	using Command = std::function<void(std::istream& args)>;

	std::unique_ptr<IDocument> m_document;

	void InsertParagraph(std::istream&);
	void InsertImage(std::istream&);
	void SetTitle(std::istream&);

	void ReplaceText(std::istream&);
	void ResizeImage(std::istream&);
	void DeleteItem(std::istream&);
	void Save(std::istream&);

	void Redo(std::istream&);
	void Undo(std::istream&);
	void List(std::istream&);
	void Help(std::istream&);

	struct EditorCommand
	{
		EditorCommand(const std::string& name, const std::string& description, const Command& command)
			: name(name)
			, description(description)
			, command(command)
		{
		}

		std::string name;
		std::string description;
		Command command;
	};
	std::vector<EditorCommand> EDITOR_COMMANDS = {
		{ "InsertParagraph", "Insert paragraph. Arguments: <position> | end <text>", std::bind(&CEditor::InsertParagraph, this, std::placeholders::_1) },
		{ "InsertImage", "Insert Image. Arguments: <position> | end <width> <height> <path>", std::bind(&CEditor::InsertImage, this, std::placeholders::_1) },
		{ "SetTitle", "Changes title. Arguments: <title>", std::bind(&CEditor::SetTitle, this, std::placeholders::_1) },
		{ "ReplaceText", "Replace text of paragraph at position. Arguments: <position> <text>", std::bind(&CEditor::ReplaceText, this, std::placeholders::_1) },
		{ "ResizeImage", "Resize image at position. Arguments: <position> <width> <height>", std::bind(&CEditor::ResizeImage, this, std::placeholders::_1) },
		{ "DeleteItem", "Delete item at position. Arguments: <position>", std::bind(&CEditor::DeleteItem, this, std::placeholders::_1) },
		{ "Save", "Save document. Arguments: <path>", std::bind(&CEditor::Save, this, std::placeholders::_1) },
		{ "Redo", "Redo undone command.", std::bind(&CEditor::Redo, this, std::placeholders::_1) },
		{ "Undo", "Undo command.", std::bind(&CEditor::Undo, this, std::placeholders::_1) },
		{ "List", "Show document.", std::bind(&CEditor::List, this, std::placeholders::_1) },
		{ "Help", "Help.", std::bind(&CEditor::Help, this, std::placeholders::_1) }
	};
};
