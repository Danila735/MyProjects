#include <locale>
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

#pragma warning (disable: 4703)

int main()
{
	// Введем строку для шифрования
	wcout << L"Enter the line you would like to encrypt(secret):" << endl;
	wstring secret;
	getline(wcin, secret);

	// Буфер для работы алгоритмов шифрования
	BYTE* buffer;

	try
	{
		// Размер строки в памяти
		size_t strAllocSize = sizeof(wstring::value_type) * secret.length();
		// Размер буфера должен быть немного больше
		size_t bufferSize = strAllocSize + 8;
		// Выделяем память под буфер
		buffer = new BYTE[bufferSize];

#pragma warning(disable:4996)
		// Копируем строку в буфер
		secret.copy(reinterpret_cast<wstring::value_type*>(buffer), secret.length(), 0);
#pragma warning(default:4996)


		//Crypto Sevice Provider
		HCRYPTPROV provider;
		// Попытаемся получить CSP
		if (!CryptAcquireContext(&provider, 0, MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
		{
			throw L"Failed to get CSP";
		}

		// Ключ для шифрования
		HCRYPTKEY key;
		// Сгенерируем ключ
		if (!CryptGenKey(provider, CALG_3DES, CRYPT_EXPORTABLE, &key))
		{
			throw L"Key Generation Error";
		}

		// Демонстрация экспорта ключа
		// Для работы этой программы не нужна, но если есть желание
		// расшифровать данные где то еще, то ключ необходим

			// Сюда будем экспортировать
		BYTE* keyBlob = 0;
		// Длина ключа
		DWORD keyBlobLength = 0;
		// Получим размер ключа
		if (!CryptExportKey(key, 0, PLAINTEXTKEYBLOB, 0, 0, &keyBlobLength))
		{
			throw L"Failed to calculate key length";
		}
		// Выделим память для ключа
		keyBlob = new BYTE[keyBlobLength];

		// Экспорт ключа
		if (!CryptExportKey(key, 0, PLAINTEXTKEYBLOB, 0, keyBlob, &keyBlobLength))
		{
			throw L"Failed to export key";
		}

		// Распечатаем его
		wcout << endl << L"Key generated(hex):" << endl;
		for (size_t i = 0; i < keyBlobLength; ++i)
		{
			wcout << hex << keyBlob[i];
		}
		wcout << endl;
		// Освободим память за ненадобностью
		delete[] keyBlob;

		// Размер наших данных для шифрования
		DWORD dataSize = strAllocSize;
		// Шифруем
		if (!CryptEncrypt(key, 0, true, 0, buffer, &dataSize, bufferSize))
		{
			throw L"Failed to encrypt data";
		}

		// Распечатаем то, что у нас получилось
		wcout << endl << L"Encrypted string(hex):" << endl;
		for (size_t i = 0; i < dataSize; ++i)
		{
			wcout << hex << buffer[i];
		}

		// Попробуем расшифровать
		wcout << endl << endl
			<< L"Let's try to decrypt it : " << endl;
		if (!CryptDecrypt(key, 0, true, 0, buffer, &dataSize))
		{
			throw L"Decrypt data failed";
		}

		// Соберем результирующую строку
		wstring received(reinterpret_cast<wchar_t*>(buffer), reinterpret_cast<wchar_t*>(buffer + dataSize));
		wcout << L"Decrypted data(received):" << endl;
		wcout << received << endl;
		wcout << endl << L"Cheking..." << endl
			<< L"(secret==received)=" << boolalpha << (secret == received) << endl;
	}
	catch (bad_alloc)
	{
		wcout << L"Memory Allocation Error" << endl;
	}
	catch (const wchar_t* const msg)
	{
		wcout << L"An exception:" << msg << endl;
	}
	if (buffer)
	{
		delete[] buffer;
	}
	system("PAUSE");
	return 0;
}