#pragma once
#include <iostream>
#include <string.h>
using namespace std;
#pragma warning(disable : 4996)
// ��ͼ������һ�����ԣ����������ķ���ʾ��������һ�������������������ʹ�øñ�ʶ�����������еľ��ӡ�
// ��Ҫ���������һЩ�̶��ķ�����һ�����;��ӵĽ�������
// ��ʱʹ�ã����һ���ض����͵����ⷢ����Ƶ���㹻�ߣ���ô���ܾ�ֵ�ý�������ĸ���ʵ������Ϊһ���������еľ��ӡ�
// �����Ϳ��Թ���һ�����������ý�����ͨ��������Щ��������������⡣
// ��ν���������﷨���������ս������ս����
// �ؼ����룺���������࣬����������֮���һЩȫ����Ϣ��һ���� HashMap��
// Ӧ��ʵ������������������ʽ���㡣
// �ŵ㣺 1������չ�ԱȽϺã��� 2���������µĽ��ͱ��ʽ�ķ�ʽ�� 3������ʵ�ּ��ķ���
// ȱ�㣺 1�������ó����Ƚ��١� 2�����ڸ��ӵ��ķ��Ƚ���ά���� 3��������ģʽ�����������͡� 4��������ģʽ���õݹ���÷�����
// ʹ�ó����� 1�����Խ�һ����Ҫ����ִ�е������еľ��ӱ�ʾΪһ�������﷨���� 2��һЩ�ظ����ֵ����������һ�ּ򵥵����������б� 
// 3��һ�����﷨��Ҫ���͵ĳ�����
// ע����������ó����Ƚ��٣�JAVA ��������������� expression4J ���档

// Discussion.Uses a class hierarchy to represent the grammar given below.When a roman numeral is provided,
// the class hierarchy validates and interprets the string.RNInterpreter "has" 4 sub - interpreters.Each sub 
// - interpreter receives the "context" (remaining unparsed string and cumulative parsed value) and contributes
// its share to the processing.Sub - interpreters simply define the Template Methods declared in the base class RNInterpreter.
//
// romanNumeral :: = { thousands } {hundreds} {tens} {ones}
// thousands, hundreds, tens, ones :: = nine | four | {five} {one} {one} {one}
// nine :: = "CM" | "XC" | "IX"
// four :: = "CD" | "XL" | "IV"
// five :: = 'D' | 'L' | 'V'
// one  :: = 'M' | 'C' | 'X' | 'I'

namespace DP_Interpreter
{
	class Thousand;
	class Hundred;
	class Ten;
	class One;

	class RNInterpreter
	{
	public:
		RNInterpreter(); // ctor for client
		RNInterpreter(int) {}
		// ctor for subclasses, avoids infinite loop
		int interpret(char*); // interpret() for client
		virtual void interpret(char *input, int &total)
		{
			// for internal use
			int index = 0;
			if (!strncmp(input, nine(), 2))
			{
				total += 9 * multiplier();
				index += 2;
			}
			else if (!strncmp(input, four(), 2))
			{
				total += 4 * multiplier();
				index += 2;
			}
			else
			{
				if (input[0] == five())
				{
					total += 5 * multiplier();
					index = 1;
				}
				else
					index = 0;
				for (int end = index + 3; index < end; index++)
					if (input[index] == one())
						total += 1 * multiplier();
					else
						break;
			}
			strcpy(input, &(input[index]));
		} // remove leading chars processed
	protected:
		// cannot be pure virtual because client asks for instance
		virtual char one() { return ' '; }
		virtual const char *four() { return ""; }
		virtual char five() { return ' '; }
		virtual const char *nine() { return ""; }
		virtual int multiplier() { return 0; }
	private:
		RNInterpreter *thousands;
		RNInterpreter *hundreds;
		RNInterpreter *tens;
		RNInterpreter *ones;
	};

	class Thousand : public RNInterpreter
	{
	public:
		// provide 1-arg ctor to avoid infinite loop in base class ctor
		Thousand(int) : RNInterpreter(1) {}
	protected:
		char one()
		{
			return 'M';
		}
		const char *four()
		{
			return "";
		}
		char five()
		{
			return '\0';
		}
		const char *nine()
		{
			return "";
		}
		int multiplier()
		{
			return 1000;
		}
	};
	class Hundred : public RNInterpreter
	{
	public:
		Hundred(int) : RNInterpreter(1) {}
	protected:
		char one()
		{
			return 'C';
		}
		const char *four()
		{
			return "CD";
		}
		char five()
		{
			return 'D';
		}
		const char *nine()
		{
			return "CM";
		}
		int multiplier()
		{
			return 100;
		}
	};

	class Ten : public RNInterpreter
	{
	public:
		Ten(int) : RNInterpreter(1) {}
	protected:
		char one()
		{
			return 'X';
		}
		const char *four()
		{
			return "XL";
		}
		char five()
		{
			return 'L';
		}
		const char *nine()
		{
			return "XC";
		}
		int multiplier()
		{
			return 10;
		}
	};

	class One : public RNInterpreter
	{
	public:
		One(int) : RNInterpreter(1) {}
	protected:
		char one()
		{
			return 'I';
		}
		const char *four()
		{
			return "IV";
		}
		char five()
		{
			return 'V';
		}
		const char *nine()
		{
			return "IX";
		}
		int multiplier()
		{
			return 1;
		}
	};

	RNInterpreter::RNInterpreter()
	{
		// use 1-arg ctor to avoid infinite loop
		thousands = new Thousand(1);
		hundreds = new Hundred(1);
		tens = new Ten(1);
		ones = new One(1);
	}
	int RNInterpreter::interpret(char *input)
	{
		int total;
		total = 0;
		thousands->interpret(input, total);
		hundreds->interpret(input, total);
		tens->interpret(input, total);
		ones->interpret(input, total);
		if (strcmp(input, ""))
			// if input was invalid, return 0
			return 0;
		return total;
	}
	void InterpreterExample()
	{
		RNInterpreter interpreter;
		char input[20];
		cout << "Enter Roman Numeral: ";
		while (cin >> input)
		{
			cout << "   interpretation is " << interpreter.interpret(input) << endl;
			cout << "Enter Roman Numeral: ";
		}
	}
}
