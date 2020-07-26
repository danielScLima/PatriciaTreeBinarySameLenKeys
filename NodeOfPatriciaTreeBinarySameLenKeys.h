#ifndef NODEOFPATRICIATREEBINARYSAMELENKEYS_H
#define NODEOFPATRICIATREEBINARYSAMELENKEYS_H

enum NodeType
{
    LEAF, BRANCH
};

/*!
 * \brief The NodeOfPatriciaTreeBinarySameLenKeys struct
 */
struct NodeOfPatriciaTreeBinarySameLenKeys
{
public:
    /*!
     * \brief NodeOfPatriciaTreeBinarySameLenKeys
     * \param nodeType
     * \param father
     */
    NodeOfPatriciaTreeBinarySameLenKeys
    (
        NodeType nodeType,
        NodeOfPatriciaTreeBinarySameLenKeys* father
    ):
        nodeType(nodeType), father(father)
    {

    }

    /*!
     * \brief ~NodeOfPatriciaTreeBinarySameLenKeys
     */
    virtual ~NodeOfPatriciaTreeBinarySameLenKeys()
    {}

    /*!
     * \brief dealockSubtree
     */
    virtual void dealockSubtree() = 0;

    NodeType nodeType = NodeType::LEAF;
    NodeOfPatriciaTreeBinarySameLenKeys* father = nullptr;
};

#endif // NODEOFPATRICIATREEBINARYSAMELENKEYS_H
