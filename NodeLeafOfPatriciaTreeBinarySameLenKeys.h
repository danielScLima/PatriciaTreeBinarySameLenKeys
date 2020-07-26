#ifndef NODELEAFOFPATRICIATREEBINARYSAMELENKEYS_H
#define NODELEAFOFPATRICIATREEBINARYSAMELENKEYS_H

#include "NodeOfPatriciaTreeBinarySameLenKeys.h"
#include <iostream>

/*!
 * \brief The NodeLeafOfPatriciaTreeBinarySameLenKeys struct
 */
struct NodeLeafOfPatriciaTreeBinarySameLenKeys:
        public NodeOfPatriciaTreeBinarySameLenKeys
{
public:
    /*!
     * \brief NodeLeaf
     * \param data
     * \param father
     * \param index
     */
    NodeLeafOfPatriciaTreeBinarySameLenKeys
    (
        const std::string& data,
        NodeOfPatriciaTreeBinarySameLenKeys* father,
        int index
    ):
        NodeOfPatriciaTreeBinarySameLenKeys(NodeType::LEAF, father),
        index(index), data(data)
    {

    }

    /*!
     * \brief dealockSubtree
     */
    virtual void dealockSubtree()
    {
        //do nothing
    }

    int index = 0;
    std::string data; //todas as leafs tem o mesmo tamanho de data
};

#endif // NODELEAFOFPATRICIATREEBINARYSAMELENKEYS_H
