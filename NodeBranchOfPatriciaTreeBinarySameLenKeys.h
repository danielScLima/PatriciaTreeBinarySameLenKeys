#ifndef NODEBRANCHOFPATRICIATREEBINARYSAMELENKEYS_H
#define NODEBRANCHOFPATRICIATREEBINARYSAMELENKEYS_H

#include "NodeOfPatriciaTreeBinarySameLenKeys.h"
#include <iostream>

/*!
 * \brief The NodeBranchOfPatriciaTreeBinarySameLenKeys struct
 */
struct NodeBranchOfPatriciaTreeBinarySameLenKeys:
        public NodeOfPatriciaTreeBinarySameLenKeys
{
public:
    /*!
     * \brief NodeBranch
     * \param father
     * \param index
     */
    NodeBranchOfPatriciaTreeBinarySameLenKeys
    (
        NodeOfPatriciaTreeBinarySameLenKeys* father,
        int index
    ):
        NodeOfPatriciaTreeBinarySameLenKeys(NodeType::BRANCH, father),
        index(index)
    {

    }

    /*!
     * \brief dealockSubtree
     */
    virtual void dealockSubtree()
    {
        left->dealockSubtree();
        delete left;
        left = nullptr;

        right->dealockSubtree();
        delete right;
        right = nullptr;
    }

    int index = 0; //A posição de diferença
    NodeOfPatriciaTreeBinarySameLenKeys* left = nullptr;//left no index (menor valor)
    NodeOfPatriciaTreeBinarySameLenKeys* right = nullptr;//right no index (maior valor)
};

#endif // NODEBRANCHOFPATRICIATREEBINARYSAMELENKEYS_H
