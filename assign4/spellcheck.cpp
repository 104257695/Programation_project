#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  Corpus tokens;
  
  auto whitespace_iters = find_all(source.begin(), source.end(), ::isspace);

  if (!whitespace_iters.empty()) {
      std::transform(
          whitespace_iters.begin(),
          whitespace_iters.end() - 1,
          whitespace_iters.begin() + 1,
          std::inserter(tokens, tokens.end()),
          [&source](auto start, auto end) {
              return Token(source, start, end);
          }
      );
  }
  
  std::erase_if(tokens, [](const Token& t) {
      return t.content.empty();
  });
  
  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  
  auto misspellings_view = source
      | rv::filter([&dictionary](const Token& t) {
          return !dictionary.contains(t.content);
      })
      | rv::transform([&dictionary](const Token& token) {
          auto suggestions = dictionary
              | rv::filter([&token](const std::string& word) {
                  return levenshtein(token.content, word) == 1;
              });
          
          return Mispelling{
              token,
              std::set<std::string>(suggestions.begin(), suggestions.end())
          };
      })
      | rv::filter([](const Mispelling& m) {
          return !m.suggestions.empty();
      });
  
  return std::set<Mispelling>(misspellings_view.begin(), misspellings_view.end());
}


#include "utils.cpp"