#include <iostream>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <cstring>
#include <memory>

class password_validator
{
  public:
    virtual bool validate(std::string_view password) = 0;
    virtual ~password_validator() {};
};

class length_validator
    : public password_validator
{
  public:
    explicit length_validator(unsigned length)
        : m_length(length)
    {
    }

    virtual bool validate(std::string_view password)
    {
        return password.size() >= m_length;
    }

  private:
    unsigned m_length;
};

class password_validator_decorator
    : public password_validator
{
  public:
    explicit password_validator_decorator(std::unique_ptr<password_validator> validator)
        : m_validator(std::move(validator))
    {
    }

    virtual bool validate(std::string_view password)
    {
        return m_validator->validate(password);
    }

  private:
    std::unique_ptr<password_validator> m_validator;
};

class digit_validator_decorator final
    : public password_validator_decorator
{
  public:
    explicit digit_validator_decorator(std::unique_ptr<password_validator_decorator> validator)
        : password_validator_decorator(std::move(validator))
    {
    }

    bool validate(std::string_view password)
    {
        if (!password_validator_decorator::validate(password))
        {
            return false;
        }

        return password.find_first_of("0123456789") != std::string::npos;
    }
};

class symbol_validator_decorator final
    : public password_validator_decorator
{
  public:
    explicit symbol_validator_decorator(std::unique_ptr<password_validator_decorator> validator)
        : password_validator_decorator(std::move(validator))
    {
    }

    bool validate(std::string_view password)
    {
        if (!password_validator_decorator::validate(password))
        {
            return false;
        }

        return password.find_first_of("!@#$%^&*(){}[]?<>") != std::string::npos;
    }
};

class case_validator_decorator final
    : public password_validator_decorator
{
  public:
    explicit case_validator_decorator(std::unique_ptr<password_validator_decorator> validator)
        : password_validator_decorator(std::move(validator))
    {
    }

    bool validate(std::string_view password)
    {
        if (!password_validator_decorator::validate(password))
        {
            return false;
        }

        bool upper = false, lower = false;

        std::for_each(password.begin(), password.end(),
                      [&upper, &lower](const char c) {
                          if (islower(c))
                              lower = true;
                          else if (isupper(c))
                              upper = true;
                      });

        return upper && lower;
    }
};

int main()
{
    using namespace std;

    string input;
    string prompt = "Enter password: ";
    string choice = "y";

    auto validator = std::make_unique<case_validator_decorator>(
        std::make_unique<symbol_validator_decorator>(
            std::make_unique<digit_validator_decorator>(
                std::make_unique<password_validator_decorator>(
                    std::make_unique<length_validator>(8)))));

    while (choice == "y")
    {
        cout << prompt;
        cin >> input;

        bool valid = validator->validate(input);

        cout << (valid ? "Valid" : "Invalid") << endl;

        cout << "Continue? (y or n): ";
        cin >> choice;
    }

    system("pause");
}