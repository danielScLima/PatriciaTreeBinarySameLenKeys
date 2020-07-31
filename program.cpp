// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "patriciatreebinarysamelenkeys.h"

TEST_CASE( "Testing the insert call in the patriciatreebinarysamelenkeys", "[single-file]" )
{
	PatriciaTreeBinarySameLenKeysDataStructure tree(5);
	
	NodeOfPatriciaTreeBinarySameLenKeys* root = tree.getRoot();
	REQUIRE (root == nullptr);
	
	REQUIRE(tree.insert("01010"));
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nleaf != nullptr);
	REQUIRE(nleaf->data.compare("01010") == 0);
	
	REQUIRE(tree.insert("01011"));
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::BRANCH);
	NodeBranchOfPatriciaTreeBinarySameLenKeys* nbranch =
	(NodeBranchOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nbranch != nullptr);
	REQUIRE(nbranch->index == 4);
	
	REQUIRE(nbranch->left->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf1 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch->left;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	REQUIRE(nbranch->right->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf2 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch->right;
	REQUIRE(nleaf2 != nullptr);
	REQUIRE(nleaf2->data.compare("01011") == 0);
	
	REQUIRE(tree.insert("11010"));
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::BRANCH);
	nbranch = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nbranch != nullptr);
	REQUIRE(nbranch->index == 0);
	
	REQUIRE(nbranch->left->nodeType == NodeType::BRANCH);
	NodeBranchOfPatriciaTreeBinarySameLenKeys* nbranch2 =
	(NodeBranchOfPatriciaTreeBinarySameLenKeys*) nbranch->left;
	REQUIRE(nbranch2 != nullptr);
	REQUIRE(nbranch2->index == 4);
	
	REQUIRE(nbranch2->left->nodeType == NodeType::LEAF);
	nleaf1 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->left;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	REQUIRE(nbranch2->right->nodeType == NodeType::LEAF);
	nleaf2 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->right;
	REQUIRE(nleaf2 != nullptr);
	REQUIRE(nleaf2->data.compare("01011") == 0);
	
	REQUIRE(nbranch->right->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf3 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch->right;
	REQUIRE(nleaf3 != nullptr);
	REQUIRE(nleaf3->data.compare("11010") == 0);
	
	REQUIRE(tree.insert("11110"));
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::BRANCH);
	nbranch = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nbranch != nullptr);
	REQUIRE(nbranch->index == 0);
	
	REQUIRE(nbranch->left->nodeType == NodeType::BRANCH);
	nbranch2 = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) nbranch->left;
	REQUIRE(nbranch2 != nullptr);
	REQUIRE(nbranch2->index == 4);
	
	REQUIRE(nbranch->right->nodeType == NodeType::BRANCH);
	NodeBranchOfPatriciaTreeBinarySameLenKeys* nbranch3 =
	(NodeBranchOfPatriciaTreeBinarySameLenKeys*) nbranch->right;
	REQUIRE(nbranch3 != nullptr);
	REQUIRE(nbranch3->index == 2);
	
	//leafs
	
	REQUIRE(nbranch2->left->nodeType == NodeType::LEAF);
	nleaf1 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->left;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	REQUIRE(nbranch2->right->nodeType == NodeType::LEAF);
	nleaf2 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->right;
	REQUIRE(nleaf2 != nullptr);
	REQUIRE(nleaf2->data.compare("01011") == 0);
	
	REQUIRE(nbranch3->left->nodeType == NodeType::LEAF);
	nleaf3 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch3->left;
	REQUIRE(nleaf3 != nullptr);
	REQUIRE(nleaf3->data.compare("11010") == 0);
	
	REQUIRE(nbranch3->right->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf4 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch3->right;
	REQUIRE(nleaf4 != nullptr);
	REQUIRE(nleaf4->data.compare("11110") == 0);
}

TEST_CASE( "Testing the remove call in the patriciatreebinarysamelenkeys", "[single-file]" )
{
	PatriciaTreeBinarySameLenKeysDataStructure tree(5);
	
	REQUIRE(tree.insert("01010"));
	REQUIRE(tree.insert("01011"));
	REQUIRE(tree.insert("11010"));
	REQUIRE(tree.insert("11110"));
	
	NodeOfPatriciaTreeBinarySameLenKeys* root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::BRANCH);
	NodeBranchOfPatriciaTreeBinarySameLenKeys* nbranch =
	(NodeBranchOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nbranch != nullptr);
	REQUIRE(nbranch->index == 0);
	
	REQUIRE(nbranch->left->nodeType == NodeType::BRANCH);
	NodeBranchOfPatriciaTreeBinarySameLenKeys* nbranch2 =
	(NodeBranchOfPatriciaTreeBinarySameLenKeys*) nbranch->left;
	REQUIRE(nbranch2 != nullptr);
	REQUIRE(nbranch2->index == 4);
	
	REQUIRE(nbranch->right->nodeType == NodeType::BRANCH);
	NodeBranchOfPatriciaTreeBinarySameLenKeys* nbranch3 =
	(NodeBranchOfPatriciaTreeBinarySameLenKeys*) nbranch->right;
	REQUIRE(nbranch3 != nullptr);
	REQUIRE(nbranch3->index == 2);
	
	//leafs
	
	REQUIRE(nbranch2->left->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf1 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->left;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	REQUIRE(nbranch2->right->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf2 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->right;
	REQUIRE(nleaf2 != nullptr);
	REQUIRE(nleaf2->data.compare("01011") == 0);
	
	REQUIRE(nbranch3->left->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf3 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch3->left;
	REQUIRE(nleaf3 != nullptr);
	REQUIRE(nleaf3->data.compare("11010") == 0);
	
	REQUIRE(nbranch3->right->nodeType == NodeType::LEAF);
	NodeLeafOfPatriciaTreeBinarySameLenKeys* nleaf4 =
	(NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch3->right;
	REQUIRE(nleaf4 != nullptr);
	REQUIRE(nleaf4->data.compare("11110") == 0);
	
	NodeOfPatriciaTreeBinarySameLenKeys* rem = tree.remove("11010");
	REQUIRE(rem != nullptr);
	delete rem;
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::BRANCH);
	nbranch = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nbranch != nullptr);
	REQUIRE(nbranch->index == 0);
	
	REQUIRE(nbranch->left->nodeType == NodeType::BRANCH);
	nbranch2 = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) nbranch->left;
	REQUIRE(nbranch2 != nullptr);
	REQUIRE(nbranch2->index == 4);
	
	//leafs
	
	REQUIRE(nbranch2->left->nodeType == NodeType::LEAF);
	nleaf1 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->left;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	REQUIRE(nbranch2->right->nodeType == NodeType::LEAF);
	nleaf2 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->right;
	REQUIRE(nleaf2 != nullptr);
	REQUIRE(nleaf2->data.compare("01011") == 0);
	
	REQUIRE(nbranch->right->nodeType == NodeType::LEAF);
	nleaf4 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch->right;
	REQUIRE(nleaf4 != nullptr);
	REQUIRE(nleaf4->data.compare("11110") == 0);
	
	rem = tree.remove("11110");
	REQUIRE(rem != nullptr);
	delete rem;
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::BRANCH);
	nbranch2 = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nbranch2 != nullptr);
	REQUIRE(nbranch2->index == 4);
	
	REQUIRE(nbranch2->left->nodeType == NodeType::LEAF);
	nleaf1 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->left;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	REQUIRE(nbranch2->right->nodeType == NodeType::LEAF);
	nleaf2 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) nbranch2->right;
	REQUIRE(nleaf2 != nullptr);
	REQUIRE(nleaf2->data.compare("01011") == 0);
	
	rem = tree.remove("01011");
	REQUIRE(rem != nullptr);
	delete rem;
	
	root = tree.getRoot();
	REQUIRE (root != nullptr);
	
	REQUIRE(root->nodeType == NodeType::LEAF);
	nleaf1 = (NodeLeafOfPatriciaTreeBinarySameLenKeys*) root;
	REQUIRE(nleaf1 != nullptr);
	REQUIRE(nleaf1->data.compare("01010") == 0);
	
	rem = tree.remove("01010");
	REQUIRE(rem != nullptr);
	delete rem;
	
	root = tree.getRoot();
	REQUIRE (root == nullptr);
	
}

TEST_CASE( "Testing the search call in the patriciatreebinarysamelenkeys", "[single-file]" )
{
	PatriciaTreeBinarySameLenKeysDataStructure tree(5);
	
	REQUIRE(tree.insert("01010"));
	REQUIRE(tree.insert("01011"));
	REQUIRE(tree.insert("11010"));
	REQUIRE(tree.insert("11110"));
	
	REQUIRE(tree.search("01010") != nullptr);
	REQUIRE(tree.search("01011") != nullptr);
	REQUIRE(tree.search("11010") != nullptr);
	REQUIRE(tree.search("11110") != nullptr);
}

TEST_CASE( "Testing the search call, case 2, in the patriciatreebinarysamelenkeys", "[single-file]" )
{
	PatriciaTreeBinarySameLenKeysDataStructure tree(5);
	
	REQUIRE(tree.insert("01010"));
	REQUIRE(tree.insert("01011"));
	REQUIRE(tree.insert("11010"));
	REQUIRE(tree.insert("11110"));
	
	REQUIRE(tree.search("01010") != nullptr);
	REQUIRE(tree.search("01011") != nullptr);
	REQUIRE(tree.search("11010") != nullptr);
	REQUIRE(tree.search("11110") != nullptr);
	
	NodeOfPatriciaTreeBinarySameLenKeys* rem = tree.remove("01010");
	REQUIRE(rem != nullptr);
	delete rem;
	rem = tree.remove("01011");
	REQUIRE(rem != nullptr);
	delete rem;
	
	REQUIRE(tree.search("01010") == nullptr);
	REQUIRE(tree.search("01011") == nullptr);
	REQUIRE(tree.search("11010") != nullptr);
	REQUIRE(tree.search("11110") != nullptr);
}


