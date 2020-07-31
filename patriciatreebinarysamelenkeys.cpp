#include "patriciatreebinarysamelenkeys.h"

#include <sstream> //for std::stringstream
#include <string>  //for std::string

bool PatriciaTreeBinarySameLenKeysDataStructure::insert(const std::string& data)
{
    bool valid = isAValidDataIoInsert(data);
    if (valid == false)
        return false;

    if (root == nullptr)
    {
        root = new NodeLeafOfPatriciaTreeBinarySameLenKeys(data, nullptr, 0);
    }
    else
    {
        NodeOfPatriciaTreeBinarySameLenKeys* tmp = root;
        while (true)
        {
            if (tmp->nodeType == NodeType::LEAF)
            {
                NodeLeafOfPatriciaTreeBinarySameLenKeys* leaf =
                        (NodeLeafOfPatriciaTreeBinarySameLenKeys*) tmp;
                bool ret = isEqualUntilPosition
                (
                    data,
                    leaf->data,
                    //leaf->index
                    leaf->data.length()-1
                );

                //Verifica se é igual até essa posição do nó
                if (ret) //deve quebrar esse nó
                {
                    int pos = isEqualUntilWhichPosition(data, leaf->data);
                    pos = pos+1; //+1 é o ponto de diferença

                    NodeOfPatriciaTreeBinarySameLenKeys* backupFather = leaf->father;
                    NodeLeafOfPatriciaTreeBinarySameLenKeys* backupLeaf = leaf;

                    //sempre a esquerda
                    NodeLeafOfPatriciaTreeBinarySameLenKeys* newLeaf =
                            new NodeLeafOfPatriciaTreeBinarySameLenKeys("", nullptr, pos);

                    if (data.at(pos) <= leaf->data.at(pos))
                    {
                        newLeaf->data = data;
                        leaf->data = leaf->data;
                    }
                    else
                    {
                        newLeaf->data = leaf->data;
                        leaf->data = data;
                    }

                    NodeBranchOfPatriciaTreeBinarySameLenKeys* nodeBranch =
                            new NodeBranchOfPatriciaTreeBinarySameLenKeys
                    (
                        backupFather,
                        pos
                    );

                    nodeBranch->left = newLeaf;
                    newLeaf->father = nodeBranch;

                    nodeBranch->right = leaf;
                    leaf->father = nodeBranch;

                    if (backupFather != nullptr)
                    {
                        //replace in father (backupFather), o leaf por nodeBranch
                        replacePointerInFather
                        (
                            (NodeBranchOfPatriciaTreeBinarySameLenKeys*) backupFather,
                            leaf,
                            nodeBranch
                        );
                    }
                    else
                    {
                        root = nodeBranch;
                    }

                    break;
                }
                else //deve quebrar antes
                {
                    //staring from root
                    //insert in the first position with the diference id
                    int pos = isEqualUntilWhichPosition(data, leaf->data);
                    pos = pos+1; //+1 é o ponto de diferença

                    NodeOfPatriciaTreeBinarySameLenKeys* prev = leaf;
                    NodeBranchOfPatriciaTreeBinarySameLenKeys* branchFather =
                            (NodeBranchOfPatriciaTreeBinarySameLenKeys*) prev->father;
                    while (branchFather != nullptr && branchFather->index > pos)
                    {
                        prev = branchFather;
                        branchFather = (NodeBranchOfPatriciaTreeBinarySameLenKeys*) prev->father;
                    }

                    //insere em prev (quebrando)
                    NodeBranchOfPatriciaTreeBinarySameLenKeys* newFather =
                            new NodeBranchOfPatriciaTreeBinarySameLenKeys(branchFather, pos);
                    if (branchFather == nullptr)
                        root = newFather;
                    NodeLeafOfPatriciaTreeBinarySameLenKeys* newLeaf =
                            new NodeLeafOfPatriciaTreeBinarySameLenKeys("", nullptr, pos);
                    newFather->left = newLeaf;
                    newLeaf->father = newFather;
                    newFather->right = prev;
                    prev->father = newFather;

                    newLeaf->data = data;
                    if (data.at(pos) == '1') //deve ficar na direita
                    {
                        NodeOfPatriciaTreeBinarySameLenKeys* temp = newFather->left;
                        newFather->left = newFather->right;
                        newFather->right = temp;
                    }

                    if (branchFather != nullptr)
                    {
                        //replace in father (branchFather), o prev por newFather
                        replacePointerInFather
                        (
                            (NodeBranchOfPatriciaTreeBinarySameLenKeys*) branchFather,
                            prev,
                            newFather
                        );
                    }
                    else
                    {
                        root = newFather;
                    }

                    break;
                }
            } //end of node leaf
            else //node is branch
            {
                //Assumindo que são dados binários
                NodeBranchOfPatriciaTreeBinarySameLenKeys* branch =
                        (NodeBranchOfPatriciaTreeBinarySameLenKeys*) tmp;
                if (data.at(branch->index) == '0')
                {
                    //é o ramo left
                    tmp = branch->left;
                }
                else //data.at(branch->index) == '1'
                {
                    //é o ramo right
                    tmp = branch->right;
                }
            }
        }
    }

    return true;
}

NodeOfPatriciaTreeBinarySameLenKeys *PatriciaTreeBinarySameLenKeysDataStructure::search
(
    const std::string& data
)
{
    bool valid = isAValidDataIoInsert(data);
    if (valid == false)
        return nullptr;

    NodeOfPatriciaTreeBinarySameLenKeys* tmp = root;
    while (tmp != nullptr)
    {
        if (tmp->nodeType == NodeType::LEAF)
        {
            //check string
            NodeLeafOfPatriciaTreeBinarySameLenKeys* leaf =
                    (NodeLeafOfPatriciaTreeBinarySameLenKeys*) tmp;
            return (leaf->data.compare(data) == 0)? leaf: nullptr;
        }
        else //tmp->nodeType == NodeType::BRANCH
        {
            NodeBranchOfPatriciaTreeBinarySameLenKeys* branch =
                    (NodeBranchOfPatriciaTreeBinarySameLenKeys*) tmp;
            char c = data.at(branch->index);

            if (c == '0')
            {
                if (branch->left != nullptr)
                    tmp = branch->left;
                else
                    return nullptr;
            }
            else //c == '1'
            {
                if (branch->right != nullptr)
                    tmp = branch->right;
                else
                    return nullptr;
            }
        }
    }

    return nullptr;
}

NodeOfPatriciaTreeBinarySameLenKeys *PatriciaTreeBinarySameLenKeysDataStructure::remove
(
    const std::string& data
)
{
    bool valid = isAValidDataIoInsert(data);
    if (valid == false)
        return nullptr;

    NodeOfPatriciaTreeBinarySameLenKeys *node = search(data);
    if (node == nullptr)
        return nullptr;

    if (node->father == nullptr) //é o root .. não existem outros nós
    {
        root = nullptr;
        return node;
    }
    else
    {
        removeBranchNodeConsideringRemovedChild
        (
            (NodeLeafOfPatriciaTreeBinarySameLenKeys*) node,
            (NodeBranchOfPatriciaTreeBinarySameLenKeys*) node->father
        );

        delete node->father;
        return node;
    }
}

void PatriciaTreeBinarySameLenKeysDataStructure::removeBranchNodeConsideringRemovedChild
(
    NodeLeafOfPatriciaTreeBinarySameLenKeys* removedLeaf,
    NodeBranchOfPatriciaTreeBinarySameLenKeys* branchToRemove
)
{
    if (branchToRemove->left == removedLeaf)
    {
        //o right vai substituir branchToRemove no pai
        if (branchToRemove->father == nullptr)
        {
            root = branchToRemove->right;
            if (branchToRemove->right != nullptr)
                branchToRemove->right->father = nullptr;
        }
        else
        {
            replacePointerInFather
            (
                (NodeBranchOfPatriciaTreeBinarySameLenKeys*) branchToRemove->father,
                branchToRemove,
                branchToRemove->right
            );

            if (branchToRemove->right != nullptr)
                branchToRemove->right->father = branchToRemove->father;
        }
    }
    else if (branchToRemove->right == removedLeaf)
    {
        //o left vai substituir branchToRemove no pai
        if (branchToRemove->father == nullptr)
        {
            root = branchToRemove->left;
            if (branchToRemove->left != nullptr)
                branchToRemove->left->father = nullptr;
        }
        else
        {
            replacePointerInFather
            (
                (NodeBranchOfPatriciaTreeBinarySameLenKeys*) branchToRemove->father,
                branchToRemove,
                branchToRemove->left
            );

            if (branchToRemove->left != nullptr)
                branchToRemove->left->father = branchToRemove->father;
        }
    }
}

bool PatriciaTreeBinarySameLenKeysDataStructure::isAValidDataIoInsert(const std::string& data)
{
    if (data.length() != this->lenOfKeys)
        return false;

    for (auto caracter: data)
    {
        if (caracter != '0' && caracter != '1')
            return false;
    }
    return true;
}

NodeOfPatriciaTreeBinarySameLenKeys *PatriciaTreeBinarySameLenKeysDataStructure::getRoot()
{
    return this->root;
}

void PatriciaTreeBinarySameLenKeysDataStructure::clearRoot()
{
    //it was already cleaned
    this->root = nullptr;
}

void PatriciaTreeBinarySameLenKeysDataStructure::replacePointerInFather
(
    NodeBranchOfPatriciaTreeBinarySameLenKeys* father,
    NodeOfPatriciaTreeBinarySameLenKeys* oldSon,
    NodeOfPatriciaTreeBinarySameLenKeys* newSon
)
{
    if (father->left == oldSon)
        father->left = newSon;
    else if (father->right == oldSon)
        father->right = newSon;
}

PatriciaTreeBinarySameLenKeysDataStructure::PatriciaTreeBinarySameLenKeysDataStructure(int lenOfKeys):
    lenOfKeys(lenOfKeys)
{
}

PatriciaTreeBinarySameLenKeysDataStructure::~PatriciaTreeBinarySameLenKeysDataStructure()
{
    if (this->root != nullptr)
    {
        this->root->dealockSubtree();
        delete this->root;
    }
}

bool PatriciaTreeBinarySameLenKeysDataStructure::isEqualUntilPosition
(
    const std::string& one,
    const std::string& two,
    int pos
)
{
    if (pos >= one.length() || pos >= two.length())
        return false;

    for (int index = 0; index <= pos; ++index)
    {
        if (one.at(index) != two.at(index))
            return false;
    }

    return true; //they are equal until such position
}

int PatriciaTreeBinarySameLenKeysDataStructure::isEqualUntilWhichPosition
(
    const std::string& one,
    const std::string& two
)
{
    if (one.length() != two.length())
        return 0; //todo: check here

    int max = -1;
    for (int index = 0; index < one.length(); ++index)
    {
        if (one.at(index) != two.at(index))
        {
            return max;//ends here
        }
        else
        {
            max = index;
        }
    }

    return max;
}

std::string PatriciaTreeBinarySameLenKeysDataStructure::getPointerAsString(NodeOfPatriciaTreeBinarySameLenKeys* node)
{
    const void * address = static_cast<const void*>(node);
    std::stringstream ss;
    ss << address;
    std::string name = ss.str();
    return "\""+name+"\"";
}

void PatriciaTreeBinarySameLenKeysDataStructure::getDrawInNode
(
    NodeOfPatriciaTreeBinarySameLenKeys *node,
    std::string &nodesDefinition,
    std::string &linksDefinition
)
{
    if (node->nodeType == NodeType::LEAF)
    {
        NodeLeafOfPatriciaTreeBinarySameLenKeys* conv =
                (NodeLeafOfPatriciaTreeBinarySameLenKeys*) node;
        nodesDefinition +=  getPointerAsString(conv)+" [shape=box label=\""+
                conv->data+"\"];";
    }
    else //NodeType::BRANCH
    {
        NodeBranchOfPatriciaTreeBinarySameLenKeys* conv =
                (NodeBranchOfPatriciaTreeBinarySameLenKeys*) node;
        nodesDefinition +=  getPointerAsString(conv)+" [shape=circle label=\""+
                std::to_string(conv->index)+"\" ];";

        if (conv->left == nullptr)
        {
            linksDefinition += getPointerAsString(conv) +" -> NULL";
        }
        else
        {
            linksDefinition += getPointerAsString(conv) +" -> "+
                    getPointerAsString(conv->left);
            getDrawInNode
            (
                conv->left,
                nodesDefinition,
                linksDefinition
            );
        }

        if (conv->right == nullptr)
        {
            linksDefinition += getPointerAsString(conv) +" -> NULL";
        }
        else
        {
            linksDefinition += getPointerAsString(conv) +" -> "+
                    getPointerAsString(conv->right);
            getDrawInNode
            (
                conv->right,
                nodesDefinition,
                linksDefinition
            );
        }
    }
}

const std::string PatriciaTreeBinarySameLenKeysDataStructure::getGraphvizDraw()
{
    std::string general = "digraph g{";
    std::string nodesDefinition;
    std::string linksDefinition;

    if (root == nullptr)
    {
        nodesDefinition += "Root [shape=none]; NULL [shape=none]";
        linksDefinition += "Root -> NULL;";
    }
    else
    {
        linksDefinition += "Root -> "+getPointerAsString(root)+";";
        getDrawInNode(root, nodesDefinition, linksDefinition);
    }

    general += nodesDefinition;
    general += linksDefinition;
    general += "}";

    return general;
}


