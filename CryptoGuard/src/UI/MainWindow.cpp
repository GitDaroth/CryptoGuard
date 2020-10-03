#include "UI/MainWindow.h"

#include <iostream>
#include "PasswordSafe.h"
#include "Utils.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
	QWidget(parent)
{
	m_ui.setupUi(this);

	//std::string masterPassword = "extremlySecurePW";

	//PasswordSafe* pws2 = new PasswordSafe("Sasa", masterPassword);
	//pws2->unlock(masterPassword);

	//PasswordEntry* pwe3 = new PasswordEntry("Facebook", "Sasa", "fabian.gulde@gmx.de", "facebookPW", masterPassword, false);
	//pws2->addPasswordEntry(pwe3);

	//pws2->lock(masterPassword);

	//pws2->writeToFile("sasa.pws");


	//PasswordSafe* pws = new PasswordSafe("Daroth", masterPassword);
	//pws->unlock(masterPassword);

	//PasswordEntry* pwe = new PasswordEntry("Facebook", "Daroth", "fabian.gulde@gmx.de", "facebookPW", masterPassword, false);
	//pws->addPasswordEntry(pwe);

	//PasswordEntry* pwe2 = new PasswordEntry("Youtube", "DarothProductions", "fabian.gulde@gmx.de", "youtubePW", masterPassword, false);
	//pws->addPasswordEntry(pwe2);

	//pws->lock(masterPassword);

	//pws->writeToFile("daroth.pws");
	//pws->readFromFile("daroth.pws");

	//PasswordSafe* pws = new PasswordSafe("daroth.pws");

	//std::string newMasterPassword = "lowSecurePW";
	//pws->changeMasterPassword(masterPassword, newMasterPassword);
	//masterPassword = newMasterPassword;

	//pws->unlock(masterPassword);

	//pws->switchPasswordEntries(0, 1);
	//pws->removePasswordEntry(0);

	//QVector<PasswordEntry*> passwordEntries = pws->getPasswordEntries();
	//qDebug() << "PWS Label:" << QString::fromStdString(pws->getLabel());
	//qDebug() << "PWS #Entries :" << pws->getPasswordEntryCount() << "\n";

	//for (PasswordEntry* entry : passwordEntries)
	//{
	//	qDebug() << QString::fromStdString(entry->getLabel());
	//	qDebug() << "User Name:" << QString::fromStdString(entry->getUserName());
	//	qDebug() << "Email:" << QString::fromStdString(entry->getEmail());
	//	qDebug() << "Password:" << QString::fromStdString(entry->getPassword(masterPassword)) << "\n";
	//}
}

MainWindow::~MainWindow()
{

}