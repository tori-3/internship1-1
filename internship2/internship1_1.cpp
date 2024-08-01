#include<iostream>
#include<string>
#include <fstream>
#include <sstream> 

//�o�������X�g
template <typename T>
class List
{
private:

    //���X�g�̊e�v�f
    struct ListElement
    {
        T data;

        ListElement* front = nullptr;

        ListElement* back = nullptr;
    };

    //���X�g�̃C�e���[�^�[(�͈�for���g������)
    class ListIterator
    {
    public:

        ListIterator(ListElement* ptr) :element{ptr}
        {

        }

        T& operator *()
        {
            return element->data;
        }

        void operator ++()
        {
            element = element->back;
        }

        bool operator !=(ListIterator& right)
        {
            return element != right.element;
        }
    private:
        ListElement* element;
    };

public:

    ListElement* begin_ptr = nullptr;
    ListElement* end_ptr = nullptr;

    //begin�̃C�e���[�^�[��Ԃ�
    ListIterator begin() const
    {
        return ListIterator{ begin_ptr };
    }

    //end�̃C�e���[�^�[��Ԃ�
    ListIterator end() const
    {
        return ListIterator{ nullptr };
    }

    //���ɗv�f��ǉ�����
    void add(const T& addData)
    {

        if (begin_ptr == nullptr)
        {
            begin_ptr = new ListElement{ addData,nullptr,nullptr };
            end_ptr = begin_ptr;
        }
        else 
        {
            end_ptr->back = new ListElement{ addData,end_ptr,nullptr };
            end_ptr->back->front = end_ptr;
            end_ptr = end_ptr->back;
        }
    }
};

int main() 
{
    //�e�X�g�R�[�h
    List<std::pair<int,std::string>> list;

    std::ifstream file;
    std::string line;

    file.open("Scores.txt", std::ios::in);

    //��s���ǂݍ���
    while (std::getline(file, line))
    {
        std::pair<int, std::string>data;

        //�^�u�ŋ�؂�A���X�g�ɒǉ�����B
        std::string temp;
        std::stringstream ss{ line };
        std::getline(ss, temp, '\t');
        data.first = atoi(temp.c_str());
        std::getline(ss, temp, '\t');
        data.second = temp;

        list.add(data);
    }

    for (const auto& data : list)
    {
        std::cout << data.first <<"\t" << data.second << std::endl;
    }
}
