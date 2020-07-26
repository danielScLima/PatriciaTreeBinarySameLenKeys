#ifndef PATRICIA_TREE_BINARY_SAME_LEN_KEYS_H
#define PATRICIA_TREE_BINARY_SAME_LEN_KEYS_H

#include <iostream>
#include <vector>

#include "NodeOfPatriciaTreeBinarySameLenKeys.h"
#include "NodeBranchOfPatriciaTreeBinarySameLenKeys.h"
#include "NodeLeafOfPatriciaTreeBinarySameLenKeys.h"

/*!
 * \brief The PatriciaTreeBinarySameLenKeys class
 */
class PatriciaTreeBinarySameLenKeys
{
private:
    NodeOfPatriciaTreeBinarySameLenKeys* root = nullptr;
    int lenOfKeys = 0;

    /*!
     * \brief getDrawInNode
     * \param node
     * \param nodesDefinition
     * \param linksDefinition
     */
    void getDrawInNode
    (
        NodeOfPatriciaTreeBinarySameLenKeys *node,
        std::string &nodesDefinition,
        std::string &linksDefinition
    );

    /*!
     * \brief getPointerAsString
     * \param node
     * \return
     */
    std::string getPointerAsString(NodeOfPatriciaTreeBinarySameLenKeys *node);

    /*!
     * \brief isEqualUntilPosition
     * \param one
     * \param two
     * \param pos
     * \return
     */
    bool isEqualUntilPosition(const std::string& one, const std::string& two, int pos);

    /*!
     * \brief isEqualUntilWhichPosition
     * \param one
     * \param two
     * \return
     */
    int isEqualUntilWhichPosition(const std::string& one, const std::string& two);

    /*!
     * \brief replacePointerInFather
     * \param father
     * \param oldSon
     * \param newSon
     */
    void replacePointerInFather
    (
        NodeBranchOfPatriciaTreeBinarySameLenKeys* father,
        NodeOfPatriciaTreeBinarySameLenKeys* oldSon,
        NodeOfPatriciaTreeBinarySameLenKeys* newSon
    );

    /*!
     * \brief removeBranchNodeConsideringRemovedChild
     * \param removedLeaf
     * \param branchToRemove
     */
    void removeBranchNodeConsideringRemovedChild
    (
        NodeLeafOfPatriciaTreeBinarySameLenKeys *removedLeaf,
        NodeBranchOfPatriciaTreeBinarySameLenKeys *branchToRemove
    );
public:
    /*!
     * \brief PatriciaTreeBinarySameLenKeys
     * \param lenOfKeys
     */
    PatriciaTreeBinarySameLenKeys(int lenOfKeys);

    ~PatriciaTreeBinarySameLenKeys();

    /*!
     * \brief getGraphvizDraw
     * \return
     */
    const std::string getGraphvizDraw();

    /*!
     * \brief insert
     * \param data
     * \return
     */
    bool insert(const std::string& data);

    /*!
     * \brief search
     * \param data
     * \return
     */
    NodeOfPatriciaTreeBinarySameLenKeys* search(const std::string& data);

    /*!
     * \brief remove
     * \param data
     * \return
     */
    NodeOfPatriciaTreeBinarySameLenKeys *remove(const std::string& data);

    /*!
     * \brief isAValidDataIoInsert
     * \param data
     * \return
     */
    bool isAValidDataIoInsert(const std::string& data);

    /*!
     * \brief getRoot
     * \return
     */
    NodeOfPatriciaTreeBinarySameLenKeys *getRoot();

};

#endif // PATRICIA_TREE_BINARY_SAME_LEN_KEYS_H
