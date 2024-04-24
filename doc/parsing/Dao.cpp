#include <iostream>
#include <string>
#include <vector>

// Definição da entidade User
class User {
private:
    int id;
    std::string name;

public:
    User(int id, const std::string& name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
};

// Interface do DAO para usuários
class UserDAO {
public:
    // Métodos virtuais puros para manipulação de usuários
    virtual User getUserById(int userId) = 0;
    virtual void insertUser(const User& user) = 0;
    virtual void updateUser(const User& user) = 0;
    virtual void deleteUser(int userId) = 0;
};

// Implementação concreta do DAO para armazenamento em memória
class MemoryUserDAO : public UserDAO {
private:
    std::vector<User> users;

public:
    // Implementação dos métodos virtuais
    User getUserById(int userId) override {
        for (const auto& user : users) {
            if (user.getId() == userId) {
                return user;
            }
        }
        throw std::runtime_error("User not found");
    }

    void insertUser(const User& user) override {
        users.push_back(user);
    }

    void updateUser(const User& user) override {
        for (auto& u : users) {
            if (u.getId() == user.getId()) {
                u = user;
                return;
            }
        }
        throw std::runtime_error("User not found");
    }

    void deleteUser(int userId) override {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->getId() == userId) {
                users.erase(it);
                return;
            }
        }
        throw std::runtime_error("User not found");
    }
};

int main() {
    // Criar uma instância do DAO
    MemoryUserDAO userDao;

    // Inserir alguns usuários
    userDao.insertUser(User(1, "Alice"));
    userDao.insertUser(User(2, "Bob"));

    // Buscar um usuário pelo ID
    try {
        User user = userDao.getUserById(1);
        std::cout << "User found: " << user.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Atualizar um usuário
    try {
        userDao.updateUser(User(1, "Alice Smith"));
        std::cout << "User updated successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Deletar um usuário
    try {
        userDao.deleteUser(2);
        std::cout << "User deleted successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
