
////////////////////////////////////
/**
 * EquationSolver.h
 */
#ifndef EQUATION_SOLVER_H
#define EQUATION_SOLVER_H
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace EquationHelper{
	class EquationSolver{
		private: 
			EquationSolver();
			static string doOperation(const string&, char, const string&);
			static void correctedString(string&);
			static void removeSpaces(string&);
			static string parse(const string&);
			static bool isSolvable(const string&);
			static void calculate(vector<string>&, vector<char>&, const string&);
		public:
			static string solve(const string&, int = 50);
	};
}
//#include "EquationSolver.cpp"
#endif