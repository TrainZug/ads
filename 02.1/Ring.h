#pragma once
#include "RingNode.h"
#include <string>
using namespace std;

class Ring {
	private:
		int AnzahlNodes;
		RingNode* anker;
	public:
		Ring ();
		~Ring();
		void addNode (string, string);
		bool search (string);
		void print ();
		void get (string &);
		friend RingNode * get_anker (Ring & r);
		friend int get_AnzahlNodes (Ring & r);
};
