#include "Interpreteur.h"


// Gestion des lexemes

char currentLexeme;

void parseLexeme()
{
	std::cin.get(currentLexeme);
}


// Gestion des tokens

struct Token
{
	enum Type
	{
		NONE,
		ENDL,
		EXIT,
		SET,
		NUM,
		VAR,
		OPAR,
		CPAR,
		PLUS,
		MINUS,
		TIMES,
		DIV,
		EQUAL
	};

	Type type;
	Frac<Int> value;
	int virgule;
};

Token current;

void parseKeyword()
{
	std::string chaine("");
	for (int i(0); i < 3; i++)
	{
		chaine += currentLexeme;
		parseLexeme();
	}

	if (chaine == "set")
	{
		current.type = Token::SET;
		return;
	}

	chaine += currentLexeme;
	parseLexeme();

	if (chaine == "exit")
	{
		current.type = Token::EXIT;
		return;
	}
}

void parseNum()
{
	if (currentLexeme >= 48 && currentLexeme <= 57 && !current.virgule)
	{
		current.value *= 10;
		current.value += int(currentLexeme - 48);
		parseLexeme();
		parseNum();
	}
	else if (currentLexeme >= 48 && currentLexeme <= 57 && current.virgule)
	{
		current.value += Frac<Int>(int(currentLexeme - 48), expoRapide(Int(10), current.virgule));
		current.virgule++;
		parseLexeme();
		parseNum();
	}
	else if (currentLexeme == '.' && !current.virgule)
	{
		current.virgule++;
		parseLexeme();
		parseNum();
	}
}

void parseToken(Token::Type expected)
{
	if (current.type != expected)
		throw std::string("Unexpected token");

	current.type = Token::NONE;
	current.value = 0;
	current.virgule = 0;

	switch (currentLexeme)
	{
		case '+':
			current.type = Token::PLUS;
			parseLexeme();
			break;

		case '-':
			current.type = Token::MINUS;
			parseLexeme();
			break;

		case '*':
			current.type = Token::TIMES;
			parseLexeme();
			break;

		case '/':
			current.type = Token::DIV;
			parseLexeme();
			break;

		case '(':
			current.type = Token::OPAR;
			parseLexeme();
			break;

		case ')':
			current.type = Token::CPAR;
			parseLexeme();
			break;

		case '=':
			current.type = Token::EQUAL;
			parseLexeme();
			break;

		case ' ':
			parseLexeme();
			parseToken(Token::NONE);
			break;

		case '\n':
			current.type = Token::ENDL;
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			current.type = Token::NUM;
			parseNum();
			break;

		case '#':
			current.type = Token::VAR;
			parseLexeme();
			parseNum();
			if (current.virgule)
				throw "Unexpected var number.";
			break;

		default:
			parseKeyword();
			break;
	}
}


// Gestion des expressions


void parseInput(Liste<Frac<Int>>& l);
void parseInstr(Liste<Frac<Int>>& l);
Frac<Int> parseExp0(Liste<Frac<Int>>& l);
Frac<Int> parseExp1(Liste<Frac<Int>>& l);
Frac<Int> parseExp1p(Liste<Frac<Int>>& l, Frac<Int> const& y);
Frac<Int> parseExp2(Liste<Frac<Int>>& l);
Frac<Int> parseExp2p(Liste<Frac<Int>>& l, Frac<Int> const& y);

void parseInput(Liste<Frac<Int>>& l)
{
	switch (current.type)
	{
		case Token::EXIT:
			parseToken(Token::EXIT);
			parseToken(Token::ENDL);
			break;

		default:
			parseInstr(l);
			parseLexeme();
			parseToken(Token::ENDL);
			parseInput(l);
			break;
	}
}

void parseInstr(Liste<Frac<Int>>& l)
{
	Frac<Int> x;
	int i;
	
	switch (current.type)
	{
		case Token::SET:
			parseToken(Token::SET);
			i = current.value.numerateur().toInt();
			parseToken(Token::VAR);
			parseToken(Token::EQUAL);
			x = parseExp2(l);
			if (i >= l.taille())
				for (int j(0); j < i + 1; j++)
					l.ajouter(0);
			l[i] = x;
			std::cout << ">>> ";
			break;

		default:
			x = parseExp2(l);
			if (l.taille() == 0)
				l.ajouter(0);
			l[0] = x;
			std::cout << "#0 = " << x << std::endl << ">>> ";
			break;
	}
}

Frac<Int> parseExp0(Liste<Frac<Int>>& l)
{
	Frac<Int> x, x0;
	int i;
	switch (current.type)
	{
		case Token::MINUS:
			parseToken(Token::MINUS);
			x0 = parseExp0(l);
			return -x0;

		case Token::OPAR:
			parseToken(Token::OPAR);
			x = parseExp2(l);
			parseToken(Token::CPAR);
			return x;

		case Token::NUM:
			x = current.value;
			parseToken(Token::NUM);
			return x;

		case Token::VAR:
			i = current.value.numerateur().toInt();
			if (i >= l.taille())
				for (int j(0); j < i + 1; j++)
					l.ajouter(0);
			x = l[i];
			parseToken(Token::VAR);
			return x;

		default:
			throw std::string("Unexpected token");
	}
}

Frac<Int> parseExp1(Liste<Frac<Int>>& l)
{
	Frac<Int> x0;
	x0 = parseExp0(l);
	return parseExp1p(l, x0);
}

Frac<Int> parseExp1p(Liste<Frac<Int>>& l, Frac<Int> const& y)
{
	Frac<Int> x0, x;
	switch (current.type)
	{
		case Token::TIMES:
			parseToken(Token::TIMES);
			x0 = parseExp0(l);
			x = parseExp1p(l, y*x0);
			return x;

		case Token::DIV:
			parseToken(Token::DIV);
			x0 = parseExp0(l);
			x = parseExp1p(l, y/x0);
			return x;

		default:
			return y;
	}
}

Frac<Int> parseExp2(Liste<Frac<Int>>& l)
{
	Frac<Int> x0;
	x0 = parseExp1(l);
	return parseExp2p(l, x0);
}

Frac<Int> parseExp2p(Liste<Frac<Int>>& l, Frac<Int> const& y)
{
	Frac<Int> x0, x;
	switch (current.type)
	{
		case Token::PLUS:
			parseToken(Token::PLUS);
			x0 = parseExp1(l);
			x = parseExp2p(l, y + x0);
			return x;

		case Token::MINUS:
			parseToken(Token::MINUS);
			x0 = parseExp1(l);
			x = parseExp2p(l, y - x0);
			return x;

		default:
			return y;
	}
}


// Interpreteurs

void lancerInterpreteur()
{
	Liste<Frac<Int>> l;

	std::cout << ">>> ";
	parseLexeme();
	parseToken(current.type);
	parseInput(l);
}
