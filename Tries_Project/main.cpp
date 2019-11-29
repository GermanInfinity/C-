/*
 * main.cpp
 * COMP15
 * Fall 2018
 * Driver for Project: A Biologist's Grep
 */

#include "Trie.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main(int argc, char *argv[])
{
    string sequence;
    char a;
    Trie tst;
    cout << " Hi, Welcome to the Genome Sequence Database! " << endl;
    cout << "To input sequences: insert with 'i' as the first character." << endl; 
    cout << "To query sequences: insert 'q' as the first character and I would return the closest match." << endl;
    cout << "To remove sequences: insert an 'r' with the sequence you want to remove from the database." << endl;

    cout << endl;
    cout << "Please, only insert sequences, query requests and remove sequences with an input file. " << endl;
    cout << "Thank you, and enjoy The Biologist's Grep!" << endl; 
    cout << endl; 
    ifstream infile;
    ofstream outfile;

    if (argc < 3){
        cerr << "You need to input three arguments." << endl;
        return -1;
    }
    else {
        infile.open(argv[1]);
        outfile.open(argv[2]);

        infile.clear();
        infile.seekg(0, ios::beg);
        if (!infile.is_open()){
            cerr << "The input file did not open." << endl;
            return -1;
        }
        if (!outfile.is_open()){
            cerr <<  "The output file did not open." << endl;
            return -1;
        }
    }

    while (infile >> a >> sequence)
        tst.manager(a, sequence, outfile);

    infile.close();
    outfile.close();
    return 0; 
    /****INSERT-TEST****/
    //Basic test case: All characters inserted into tree.
    //insert_test();
    //tst.post_order_print();
    //tst.print();
    //Expected output: ATTTACCGTR
    //Actual output: ATTTACCGTR
    //Sequences: A C G T ATTA

    //Second case: more inputs
    //Expected output: ATTACGGCGCCGTAAT
    //Actual output: ATTACGGCGCCGTAAT
    //Sequences: A ATTA C CGGC G GCCG T TAAT

    //Question mark case
    //insert_question_mark_test();
    //Expected output: ACGTAACGTCACGTGACGTTR
    //Actual output: ACGTAACGTCACGTGACGTTR
    //Sequence: AA  AC  AG  AT   CA  CC  CG  CT  
    // GA  GC  GG  GT   TA  TC  TG  TT 

    //Second case: question marks and characters
    //Expected output: ACGTGAACGTGCACGTGGACGTGTAR
    //Actual output: ACGTGAACGTGCACGTGGACGTGTAR
    //Sequences: AAGA  AAGC  AAGG  AAGT    ACGA  ACGC  
    // ACGG  ACGT    AGGA  AGGC  AGGG  AGGT    ATGA  ATGC  ATGG  ATGT  

    //Third case: another question mark inserted into the tree
    //Sequences: AAGA  AAGC  AAGG  AAGT    ACGA  ACGC  ACGG  ACGT  
    //AGGA  AGGC  AGGG  AGGT    ATGA  ATGC  ATGG  ATGT     GA  GC  GG  GT  
    //tst.post_order_print();
    //tst.print();


    /****REMOVE****/
    //Basic test case: 
    //tst.remove_test()
    //Expected: only sequence AC in trie
    //Actual: Only sequence AC in trie, but returns no match found. 
    
    //Second case: Remove a sequence from a wild character insertion
    //tst.remove_test()
    //Expected: removes the sequence AC from A? 
    //Actual: AA  A  AG  AT 
    //Third case: Remove a sequence from a wild character insertion
    //tst.remove_test()
    //Expected: removes the sequence AC from A? 
    //Actual: AA  A  AG  AT  

    /****QUERY****/
    //tst.query_test();
    //Match found ACTTTACATG 0.916667 
    //Second case: In tree, ACG, Query ACG
    //tst.query_test();
    //Match found ACG 100
    //Third case: In tree, ACG, Query A?
    //tst.query_test();
    //Match found ACG 0.666667
    //Fourth case: In tree ACG, Query AC
    //tst.query_test(); 
    //Match found AC 0.666667
  
}
/*
void insert_test()
{
    tst.insert_sequence('A'); 
    tst.insert_sequence('C');
    tst.insert_sequence('G');
    tst.insert_sequence('T');
    tst.insert_sequence('ATTA');
    //Second case: more inputs. 
    tst.insert_sequence('CGGC');
    tst.insert_sequence('GCCG');
    tst.insert_sequence('TAAT');

}

void insert_question_mark_test()
{
    tst.insert_sequence('?'); 
    tst.insert_sequence('??');
    //Second case: question marks and characters 
    tst.insert_sequence('A?G?');
    //Third case: with another another question mark inserted. 
    tst.insert_sequence('G?');

}


void query_test()
{
    tst.query('ACT?TTACATG');
    //Second case: q ACG
    tst.query('ACG');
    //Third case: q A? 
    tst.query('A?');
    //Fourth case: q AC
    tst.query('AC');
}


void remove_test()
{
    //First case: not actually deleting anything
    tst.insert('A');
    tst.insert('AC');
    tst.remove('A');

    //Second case: remove everything from the tree
    tst.insert('ACG');
    tst.remove('ACG');

    //Third case: wild cards
    tst.insert('A?');
    tst.remove('AC');

    //Fourth case: asteriks
    tst.insert('A?');
    tst.remove('A*');

}*/