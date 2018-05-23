﻿#include "stdafx.h"
#include "CCommandHistory.h"

bool CCommandHistory::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

void CCommandHistory::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute(); // может выбросить исключение
		--m_nextCommandIndex;
	}
}

bool CCommandHistory::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void CCommandHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute(); // может выбросить исключение
		++m_nextCommandIndex;
	}
}

void CCommandHistory::SetAndExecuteCommand(std::unique_ptr<ICommand>&& command)
{
	if (m_nextCommandIndex < m_commands.size()) // Не происходит расширения истории команд
	{
		command->Execute(); // может бросить исключение
		++m_nextCommandIndex; //
		m_commands.resize(m_nextCommandIndex); // исключение выброшено не будет, т.к. размер <= текущему
		m_commands.back() = move(command);
	}
	else // будет происходить расширение истории команд
	{
		assert(m_nextCommandIndex == m_commands.size());
		// резервируем место по добавляемую команду
		m_commands.emplace_back(nullptr); // может выбросить исключение, но мы еще ничего не трогали

		try
		{
			command->Execute(); // может выбросить исключение
			// заменяем команду-заглушку

			if (m_nextCommandIndex == MAX_SIZE)
			{
				//удаляем из начала,если история заполнилась
				m_commands.pop_front();
				--m_nextCommandIndex;
			}

			m_commands.back() = move(command); // не бросает исключений
			++m_nextCommandIndex; // теперь можно обновить индекс следующей команды
		}
		catch (...)
		{
			// удаляем заглушку, т.к. команда не исполнилась
			m_commands.pop_back(); // не бросает исключений
			// перевыбрасываем пойманное исключение вверх (кем бы оно ни было),
			// т.к. команду выполнить не смогли
			throw;
		}
	}
}