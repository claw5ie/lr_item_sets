void
print_grammar(Grammar &grammar)
{
  std::cout << "\nGrammar:\n";
  for (auto &rule: grammar.rules)
    std::cout << "    " << rule_to_string(grammar, rule) << '\n';
  std::cout << '\n';
}

void
print_pushdown_automaton(Grammar &grammar, ParsingTable &table)
{
  for (auto &state: table)
    {
      std::cout << "State " << state.id << ":\n    ";
      for (auto &actions: state.actions)
        {
          switch (actions.type)
            {
            case Action_Reduce:
              {
                std::cout << "r("
                          << rule_to_string(grammar, *actions.as.reduce.to_rule)
                          << ")";
              }

              break;
            case Action_Shift:
              {
                auto symbol = actions.as.shift.label;

                std::cout << '\'';

                if (is_variable(symbol))
                  std::cout << grammar.grab_variable_name(symbol);
                else
                  std::cout << (TerminalType)symbol;

                std::cout << "\' -> "
                          << actions.as.shift.item->id;
              }

              break;
            }

          std::cout << "; ";
        }

      std::cout << '\n';

      for (auto &item: state.itemset)
        {
          std::cout << grammar.grab_variable_name((*item.rule)[0])
                    << ": ";

          size_t i = 1;
          for (; i + 1 < item.rule->size(); i++)
            {
              if (i == item.dot_index)
                std::cout << '.';

              auto symbol = (*item.rule)[i];

              if (is_variable(symbol))
                std::cout << grammar.grab_variable_name(symbol);
              else
                std::cout << (TerminalType)symbol;
            }

          if (i == item.dot_index)
            std::cout << '.';

          std::cout << '\n';
        }

      std::cout << '\n';
    }
}
