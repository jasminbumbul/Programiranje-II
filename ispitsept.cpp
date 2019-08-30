#include <iostream>
#include <vector>
#include <regex>

using namespace std;

const char* crt = "\n---------------------------------------\n";

char* alociraj(const char* s) {
	if (s != nullptr) {
		int vel = strlen(s) + 1;
		char* temp = new char[vel];
		strcpy_s(temp, vel, s);
		return temp;
	}
	return nullptr;
}

class Datum
{
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000)
	{
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& obj)
	{
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj)
	{
		if (&obj == this)
		{
			return *this;
		}
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		return *this;
	}
	~Datum()
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	bool operator==(Datum& obj)
	{
		return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina;
	}
	int toDani() {
		return *_dan + *_mjesec * 30 + *_godina * 365;
	}
	friend ostream& operator<< (ostream& COUT, const Datum& obj)
	{
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};

class Izuzetak :public exception
{
	string _datum;//KORISTITE DANASNJI DATUM
	string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
	int    _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK
public:
	Izuzetak(const char* poruka, string datum, string funkcija, int linija) :exception(poruka)
	{
		_datum = datum;
		_funkcija = funkcija;
		_linija = linija;
	}
	friend ostream& operator<<(ostream& cout, const Izuzetak& obj)
	{
		cout << "Datum: " << obj._datum << endl;
		cout << "Funkcija: " << obj._funkcija << endl;
		cout << "Linija: " << obj._linija << endl;
		cout << "Greska: " << obj.what() << endl;
		return cout;
	}
};

template<class T1, class T2, int max>
class Kolekcija
{
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutno;
public:
	Kolekcija()
	{
		_trenutno = new int(0);
	}
	Kolekcija(const Kolekcija& obj)
	{
		for (size_t i = 0; i < *obj._trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
		_trenutno = new int(*obj._trenutno);
	}
	Kolekcija& operator=( Kolekcija& obj)
	{
		if (&obj==this)
		{
			return *this;
		}
		for (size_t i = 0; i < *obj._trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
		_trenutno = new int(*obj._trenutno);
			return *this;
	}
	~Kolekcija()
	{
		delete _trenutno; _trenutno = nullptr;
	}
	void AddElement(const T1& element1, const T2& element2)
	{
		if (*_trenutno==max-1)
		{
			throw Izuzetak("Kolekcija je puna",__DATE__,__FUNCTION__,__LINE__);
		}
		_elementi1[*_trenutno] = element1;
		_elementi2[*_trenutno] = element2;
		(*_trenutno)++;
	}
	int getTrenutno() { return *_trenutno; }
	T1 getElement1(int index) { return _elementi1[index]; }
	T2 getElement2(int index) { return _elementi2[index]; }
	int getMax() { return max; }
	friend ostream& operator<<(ostream& cout,  Kolekcija& obj)
	{
		for (size_t i = 0; i < obj.getTrenutno(); i++)
		{
			cout << obj.getElement1(i) << "  " << obj.getElement2(i) << endl;
		}
		return cout;
	}
};

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
const char* enumKurseviChar[] = { "HtmlCSSJavaScript", "SoftwareEngeneeringFundamentals", "MasteringSQL", "WindowsSecurity " };

class Kurs
{
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char* _imePredavaca;
public:
	Kurs()
	{
		_kurs = enumKursevi::HtmlCSSJavaScript;
		_pocetak = Datum();
		_kraj = Datum();
		_imePredavaca = nullptr;
	}

	Kurs(enumKursevi kurs, const char* ime, Datum pocetak, Datum kraj) {
		_kurs = kurs;
		_pocetak = pocetak;
		_kraj = kraj;
		_imePredavaca = alociraj(ime);
	}
	Kurs(const Kurs& obj)
	{
		_kurs = obj._kurs;
		_pocetak = obj._pocetak;
		_kraj = obj._kraj;
		_imePredavaca = alociraj(obj._imePredavaca);
	}
	Kurs& operator=(const Kurs& obj)
	{
		if (&obj == this)
		{
			return *this;
		}
		_kurs = obj._kurs;
		_pocetak = obj._pocetak;
		_kraj = obj._kraj;
		_imePredavaca = alociraj(obj._imePredavaca);
		return *this;
	}
	~Kurs()
	{
		delete[]_imePredavaca; _imePredavaca = nullptr;

	}
	bool operator==(Kurs& obj)
	{
		return _kurs == obj._kurs && _pocetak == obj._pocetak && obj._kraj == _kraj && strcmp(_imePredavaca, obj._imePredavaca) == 0;
	}
	enumKursevi getKurs() { return _kurs; }
	Datum getPocetak() {
		return _pocetak;
	}
	Datum getKraj() {
		return _kraj;
	}
	friend ostream& operator<<(ostream& cout, Kurs& obj) {
		cout << "Kurs: " << enumKurseviChar[obj.getKurs()] << endl;
		cout << "Trajanje kursa: " << obj._pocetak << "  -  " << obj._kraj << endl;
		cout << "Ime predavaca: " << obj._imePredavaca << endl;
		return cout;
	}
};


class Polaznik
{
	static int ID;
	const int _polaznikID;
	//SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
	char* _imePrezime;
	string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
	Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
	//INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
	Polaznik(const char* imePrezime, string telefon) : _polaznikID(ID++)
	{
		_imePrezime = alociraj(imePrezime);
		_kontaktTelefon = telefon;
	}
	Polaznik& operator=(Polaznik& obj)
	{
		if (&obj == this)
		{
			return *this;
		}
		_imePrezime = alociraj(obj._imePrezime);
		_kontaktTelefon = obj._kontaktTelefon;
		for (size_t i = 0; i < obj._uspjesnoOkoncaniKursevi.getTrenutno(); i++)
		{
			_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*obj._uspjesnoOkoncaniKursevi.getElement1(i)), obj._uspjesnoOkoncaniKursevi.getElement2(i));
		}
		return *this;
	}
	bool operator==(Polaznik& obj)
	{
		return _polaznikID == obj._polaznikID;
	}
	~Polaznik()
	{
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<<(ostream& cout, Polaznik& obj)
	{
		cout << "ID: " << obj._polaznikID << endl;
		cout << "Ime i prezime: " << obj._imePrezime << endl;
		cout << "Kontakt telefon: " << obj._kontaktTelefon << endl;
		cout << "Uspjesno okoncani kursevi: " << endl;
		cout << obj._uspjesnoOkoncaniKursevi << endl;
		return cout;
	}
};

int Polaznik::ID = 1;

class SkillsCentar
{
	string _nazivCentra;
	vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
	Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
public:
	SkillsCentar(string naziv) { _nazivCentra = naziv; }
	SkillsCentar(const SkillsCentar& obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti)
	{
		_nazivCentra = obj._nazivCentra;
	}
	bool ProvjeriKoliziju(Kurs kurs)
	{
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i].getPocetak().toDani() < kurs.getKraj().toDani()) {
				return false;
			}
		}
		return true;
	}
	void AddKurs(Kurs& kurs)
	{
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i]==kurs)
			{
				throw Izuzetak("Kurs vec postoji", __DATE__, __FUNCTION__, __LINE__);
			}
		}
		_kursevi.push_back(kurs);
	}
	void AddAplikaciju(Kurs& kurs, Polaznik& polaznik)
	{
		for (size_t i = 0; i < _aplikanti.getTrenutno(); i++)
		{
			if (_aplikanti.getElement1(i)==kurs && *_aplikanti.getElement2(i) == polaznik)
			{
				throw Izuzetak("Polaznik je vec na tom kursu", __DATE__, __FUNCTION__, __LINE__);
			}

		}
		bool flag = false;
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i]==kurs)
			{
				flag = true;
			}
		}
		if (!flag)
		{
			throw Izuzetak("Kurs ne postoji u centru", __DATE__, __FUNCTION__, __LINE__);

		}
		_aplikanti.AddElement(kurs, new Polaznik(polaznik));
	}
};

bool ProvjeriFormatTelefona(string telefon)
{
	regex pravilo("\\(\\d{3}\\)\\d{3}\\-\\d{3}");
	return regex_match(telefon, pravilo);
}

void main()
{
	/****************************************************************************
	// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
	//    RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
	// 3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
	// 4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
	// 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U
	//    TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE,
	//    POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	// 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int, 10> kolekcija1;
	try
	{
		for (size_t i = 0; i < kolekcija1.getMax(); i++)
			kolekcija1.AddElement(i, i + 2);
		//FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
		cout << kolekcija1.getElement1(0) << " " << kolekcija1.getElement2(0) << endl;
		cout << kolekcija1.getElement1(20) << " " << kolekcija1.getElement2(20) << endl;
		//FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
	}
	catch (Izuzetak & err)
	{
		cout << "Greska -> " << err << endl;
	}

	cout << kolekcija1 << endl;
	Kolekcija<int, int, 10> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int, 10> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeKursa
	Kurs sef(SoftwareEngeneeringFundamentals,"Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
	cout << sef << endl;
	Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
	sef = msql;
	if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
		cout << "ISTI SU KURSEVI" << endl;
	Kurs msql2(msql);
	cout << msql2 << endl;
#pragma endregion

#pragma region TestiranjePolaznika
	string telefon1 = "(061)111-111";
	string telefon2 = "(061)111222";
	string telefon3 = "(061)111-333";

	if (!ProvjeriFormatTelefona(telefon1))
		cout << "Broj " << telefon1 << " nije validan" << endl;
	if (!ProvjeriFormatTelefona(telefon2))
		cout << "Broj " << telefon2 << " nije validan" << endl;
	if (!ProvjeriFormatTelefona(telefon3))
		cout << "Broj " << telefon3 << " nije validan" << endl;


	Polaznik denis("Denis Music", telefon1);
	Polaznik denis2("Denis2 Music2", telefon3);

#pragma endregion

//#pragma region TestiranjeCentra
	try
	{
		SkillsCentar mostar("Skills Center Mostar");
		if (mostar.ProvjeriKoliziju(sef)) //JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA I
			mostar.AddKurs(sef);          //KURSA SE NE SMIJE POKLAPAT
		if (mostar.ProvjeriKoliziju(msql))
			mostar.AddKurs(msql);
		if (mostar.ProvjeriKoliziju(msql2))
			mostar.AddKurs(msql2);
		//ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
		mostar.AddAplikaciju(sef, denis);
		//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
		//mostar.AddAplikaciju(msql, denis);
		//mostar.AddAplikaciju(msql, denis);
		//ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
		cout << denis2 << endl;
		denis2 = denis;
		if (denis == denis2) //POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
			cout << "ISTI SU" << endl;

//		mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);
//		// BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU 
//		// DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE 
//		// POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
//		mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);
//		vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);
//		//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS
//
//		if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
//			cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;
//
//		SkillsCentar sarajevo = mostar;
//		cout << sarajevo << endl;
	}
	catch (Izuzetak & err)
	{
		cout << err << endl;
	}
//#pragma endregion
	system("pause");
}

































//#include<iostream>
//#include<vector>
//using namespace std;
//
//const char* crt = "\n-----------------------------------------------\n";
//
//enum Status { ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA };
//enum Sortiranje { RASTUCI, OPADAJUCI };
//enum Drzava { SAD, AUSTRALIJA, ENGLESKA };
//
//char* Alociraj(const char* sadrzaj)
//{
//	if (sadrzaj==nullptr)
//	{
//		return nullptr;
//	}
//	int vel = strlen(sadrzaj) + 1;
//	char* tempChar = new char[vel];
//	strcpy_s(tempChar, vel, sadrzaj);
//	return tempChar;
//}
//
//class Datum {
//	int* _dan, * _mjesec, * _godina;
//public:
//	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
//		_dan = new int(dan);
//		_mjesec = new int(mjesec);
//		_godina = new int(godina);
//	}
//	Datum(const Datum& obj)
//	{
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//	}
//	Datum& operator=(const Datum& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		return *this;
//	}
//	~Datum() {
//		delete _dan; _dan = nullptr;
//		delete _mjesec; _mjesec = nullptr;
//		delete _godina; _godina = nullptr;
//	}
//	Datum&  operator++()
//	{
//		++(*_dan);
//		return * this;
//	}
//	int toDane() {
//		return *_dan + *_mjesec * 30 + *_godina * 365;
//	}
//	bool operator==(Datum& obj) {
//		return *_dan == *obj._dan&& * _mjesec == *obj._mjesec && * _godina == *obj._godina;
//	}
//	friend ostream& operator<< (ostream& COUT, Datum& obj) {
//		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
//		return COUT;
//	}
//};
//
//template<class T1, class T2, int max>
//class FITKolekcija {
//	T1* _elementi1[max];
//	T2* _elementi2[max];
//	int _trenutno;
//public:
//	FITKolekcija() {
//		for (size_t i = 0; i < max; i++) {
//			_elementi1[i] = nullptr;
//			_elementi2[i] = nullptr;
//		}
//		_trenutno = 0;
//	}
//	FITKolekcija(const FITKolekcija& obj)
//	{
//		_trenutno = obj._trenutno;
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = new T1(*obj._elementi1[i]);
//			_elementi2[i] = new T2(*obj._elementi2[i]);
//		}
//	}
//	FITKolekcija& operator=(const FITKolekcija& obj)
//	{
//		if (&obj == this)
//		{
//			return *this;
//		}
//		_trenutno = obj._trenutno;
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = new T1(*obj._elementi1[i]);
//			_elementi2[i] = new T2(*obj._elementi2[i]);
//		}
//		return *this;
//	}
//	~FITKolekcija() {
//		for (size_t i = 0; i < max; i++) {
//			delete _elementi1[i]; _elementi1[i] = nullptr;
//			delete _elementi2[i]; _elementi2[i] = nullptr;
//		}
//	}
//	void Dodaj(const T1& element1, const T2& element2)
//	{
//		if (_trenutno==max-1)
//		{
//			throw exception("Kolekcija je puna");
//		}
//		_elementi1[_trenutno] = new T1(element1);
//		_elementi2[_trenutno] = new T2(element2);
//		_trenutno++;
//	}
//	T1** GetT1() { return _elementi1; }
//	T2** GetT2() { return _elementi2; }
//	int GetTrenutno() { return _trenutno; }
//	void Sortiraj(Sortiranje sort)
//	{
//		bool flag = true;
//		if (sort==0)
//		{
//			while (flag)
//			{
//				flag = false;
//				for (size_t i = 0; i < _trenutno-1; i++)
//				{
//					if (*_elementi1[i]>*_elementi1[i+1])
//					{
//						swap(_elementi1[i], _elementi1[i + 1]);
//						swap(_elementi2[i], _elementi2[i + 1]);
//						flag = true;
//					}
//				}
//			}
//			return;
//		}
//		else
//		{
//			while (flag)
//			{
//				flag = false;
//				for (size_t i = 0; i < _trenutno - 1; i++)
//				{
//					if (*_elementi1[i] < * _elementi1[i + 1])
//					{
//						swap(_elementi1[i], _elementi1[i + 1]);
//						swap(_elementi2[i], _elementi2[i + 1]);
//						flag = true;
//					}
//				}
//			}
//		}
//	}
//	friend ostream& operator<< (ostream& COUT, FITKolekcija& obj) {
//		for (size_t i = 0; i < obj._trenutno; i++)
//			COUT << *obj._elementi1[i] << " " << *obj._elementi2[i] << endl;
//		return COUT;
//	}
//};
//
//
//class Viza {
//protected:
//	Drzava _drzava;
//	Datum _vazenjeOD;
//	Datum _vazenjeDO;
//	char* _napomena;
//	// string se odnosi na razlog promjene statusa, a moguće je samo 10 izmjena statusa
//	FITKolekcija<Status, string, 10> _statusi;
//public:
//	Viza(Drzava drzava, Datum _OD, Datum _DO,const char* napomena = nullptr) :_vazenjeDO(_DO), _vazenjeOD(_OD)
//	{
//		if (napomena != nullptr) {
//			_napomena = new char[strlen(napomena) + 1];
//			strcpy_s(_napomena, strlen(napomena) + 1, napomena);
//		}
//		else
//			_napomena = nullptr;
//		_drzava = drzava;
//	}
//	Viza(const Viza& obj)
//	{
//		_drzava = obj._drzava;
//		_vazenjeDO = obj._vazenjeDO;
//		_vazenjeOD = obj._vazenjeOD;
//		_napomena = Alociraj(obj._napomena);
//	}
//	Viza& operator=(const Viza& obj)
//	{
//		if (&obj == this)
//		{
//			return *this;
//		}
//		_drzava = obj._drzava;
//		_vazenjeDO = obj._vazenjeDO;
//		_vazenjeOD = obj._vazenjeOD;
//		_napomena = Alociraj(obj._napomena);
//		return *this;
//	}
//	~Viza() { delete[] _napomena; _napomena = nullptr; }
//	Datum GetVazenjeOD() { return _vazenjeOD; }
//	Datum GetVazenjeDO() { return _vazenjeDO; }
//	char* GetNapomena() { return _napomena; }
//	Drzava getDrzava() { return _drzava; }
//	FITKolekcija<Status, string, 10>& GetStatuse() { return _statusi; }
//	virtual void Info() = 0;
//};
//
//class PoslovnaViza :public Viza {
//	string _kompanija; //naziv kompanije koja potvrđuje da posluje sa aplikantom
//public:
//	PoslovnaViza(Drzava drzava, Datum _OD, Datum _DO, string kompanija,const char* napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
//		_kompanija = kompanija;
//	}
//	PoslovnaViza(const PoslovnaViza& obj):Viza(obj)
//	{
//		_kompanija = obj._kompanija;
//	}
//	PoslovnaViza& operator=(const PoslovnaViza& obj)
//	{
//		(Viza&)(*this) = obj;
//		_kompanija = obj._kompanija;
//		return *this;
//
//	}
//	friend ostream& operator << (ostream& COUT, PoslovnaViza& obj) {
//		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._kompanija << endl;
//		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
//		COUT << "STATUSI -> " << obj._statusi << endl;
//		return COUT;
//
//	}
//	 void Info() {};
//
//};
//class TuristickaViza : public Viza {
//	string _adresa; //adresa hotele ili drugog smještaja na kojoj će aplikant boraviti
//public:
//	TuristickaViza(Drzava drzava, Datum _OD, Datum _DO, string adresa,const char* napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
//		_adresa = adresa;
//	}
//	friend ostream& operator << (ostream& COUT, TuristickaViza& obj) {
//		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._adresa << endl;
//		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
//		COUT << "STATUSI -> " << obj._statusi << endl;
//		return COUT;
//
//	}
//	 void Info() {};
//};
//
//class Aplikant {
//	char* _imePrezime;
//	Datum* _datumRodjenja;
//	char* _brojPasosa;
//	vector<Viza*> _vize;
//public:
//	Aplikant(const char* imePrezime, Datum datumRodjenja,const  char* brPasosa) {
//		int vel = strlen(imePrezime) + 1;
//		_imePrezime = new char[vel];
//		strcpy_s(_imePrezime, vel, imePrezime);
//		vel = strlen(brPasosa) + 1;
//		_brojPasosa = new char[vel];
//		strcpy_s(_brojPasosa, vel, brPasosa);
//		_datumRodjenja = new Datum(datumRodjenja);
//	}
//	Aplikant(const Aplikant& obj)
//	{
//		_imePrezime = Alociraj(obj._imePrezime);
//		_datumRodjenja = new Datum(*obj._datumRodjenja);
//		_brojPasosa = Alociraj(obj._brojPasosa);
//		_vize = obj._vize;
//	}
//	Aplikant& operator=(const Aplikant& obj)
//	{
//		_imePrezime = Alociraj(obj._imePrezime);
//		_datumRodjenja = new Datum(*obj._datumRodjenja);
//		_brojPasosa = Alociraj(obj._brojPasosa);
//		_vize = obj._vize;
//		return *this;
//	}
//	~Aplikant() {
//		delete[]_imePrezime; _imePrezime = nullptr;
//		delete[]_brojPasosa; _brojPasosa = nullptr;
//		delete _datumRodjenja; _datumRodjenja = nullptr;
//		for (size_t i = 0; i < _vize.size(); i++)
//		{
//			delete _vize[i]; _vize[i] = nullptr;
//		}
//	}
//	friend ostream& operator << (ostream& COUT, Aplikant& obj) {
//		COUT << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._brojPasosa << endl;
//		COUT << "VIZE -> " << endl;
//		for (size_t i = 0; i < obj._vize.size(); i++)
//			COUT << obj._vize[i] << endl;
//		return COUT;
//	}
//	bool DodajVizu(Viza* viza)
//	{
//		if (_datumRodjenja->toDane()<3650)
//		{
//			cout << "Aplikant je mladji od 10 godina" << endl;
//			return false;
//		}
//		for (size_t i = 0; i < _vize.size(); i++)
//		{
//			if (_vize[i]->getDrzava() == viza->getDrzava() && _vize[i]->GetVazenjeDO().toDane() > viza->GetVazenjeOD().toDane()) {
//				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
//				{
//					if (*_vize[i]->GetStatuse().GetT1()[j] == Status::IZDATA) return false;
//				}
//			}
//			if (_vize[i]->getDrzava() == Drzava::SAD && viza->getDrzava() == Drzava::SAD) {
//				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
//				{
//					if (*_vize[i]->GetStatuse().GetT1()[j] == Status::PONISTENA)
//						return false;
//				}
//			}
//		}
//		
//		if (dynamic_cast<TuristickaViza*>(viza)!=nullptr)
//		{
//			_vize.push_back(new TuristickaViza(*dynamic_cast<TuristickaViza*>(viza)));
//		}
//		else
//			if (dynamic_cast<PoslovnaViza*>(viza) != nullptr)
//			{
//				_vize.push_back(new PoslovnaViza(*dynamic_cast<PoslovnaViza*>(viza)));
//			}
//		return true;
//	}
//	bool DodajStatus(Viza* viza, Status status,string poruka)
//	{
//		//enum Status { ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA };
//
//		bool flag = false;
//		for (size_t i = 0; i < _vize.size(); i++)
//		{
//			if (_vize[i]==viza)
//			{
//				if (status==Status::ZAHTJEV_ZAPRIMLJEN && )
//				{
//
//				}
//			}
//		}
//	}
//	vector<Viza* > GetVize() { return _vize; }
//};
//
//void main() {
//
//	/****************************************************************************
//	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
//	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
//	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
//	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
//	****************************************************************************/
//
//
//	Datum danas(15, 2, 2017);
//	Datum sutra(++danas); // inkrementiranjem se uvecava dan za 1
//	Datum prekosutra;
//	Datum dat15022017(15, 2, 2017), dat18082017(18, 8, 2017), dat11052018(11, 5, 2018), dat11122017(11, 12, 2017);
//
//
//	prekosutra = danas;
//	if (prekosutra == danas)
//		cout << "Datumi su jednaki" << endl;
//	cout << danas << endl << sutra << endl << prekosutra << crt;
//
//	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;
//
//	FITKolekcija<int, int, 7> brojevi;
//	brojevi.Dodaj(v196, v6);
//	brojevi.Dodaj(v13, v32);
//	brojevi.Dodaj(v98, v196);
//	brojevi.Dodaj(v63, v13);
//	brojevi.Dodaj(v98, v196);
//	brojevi.Dodaj(v196, v6);
//
//	cout << brojevi << crt;
//	//NA KOJI NAČIN ĆE SE VRŠITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, A VRŠI SE NA OSNOVU VRIJEDNOSTI TIPA T1
//	brojevi.Sortiraj(RASTUCI);
//	cout << brojevi << crt;
//	brojevi.Sortiraj(OPADAJUCI);
//	cout << brojevi << crt;
//
//	try
//	{
//		//U SLUČAJU PREKORAČENJA DEFINISANE VELIČINE KOLEKCIJE, POTREBNO JE BACITI IZUZETAK
//		brojevi.Dodaj(v13, v196);
//	}
//	catch (exception & err)
//	{
//		cout << "Error -> " << err.what() << endl;
//	}
//
//	Aplikant jasmin("Jasmin Azemovic", Datum(15, 5, 1979), "BS6985645");
//	PoslovnaViza poslovna(SAD, dat15022017, dat18082017, "Microsoft");
//
//	/*
//	NOVA VIZA SE NE MOŽE DODATI UKOLIKO:
//	- JE APLIKANT MLAĐI OD 10 GODINA
//	- U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAŽEĆA (POJAM VAŽEĆA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. DA VIZA NIJE PONIŠTENA ILI ISTEKLA) VIZA ZA TU DRŽAVU, BEZ OBZIRA NA NJENU VRSTU.
//	- JE NEKA OD RANIJIH VIZA PONIŠTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRŽAVU: SAD)
//	*/
//	if (jasmin.DodajVizu(&poslovna))
//		cout << "Podaci o vizi uspješno zaprimljeni" << endl;
//	/*
//	STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
//	- NIJE MOGUĆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
//	- NIJE MOGUĆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA
//	*/
//	if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti navode sa predstavnicima kompanije Microsoft"))
//		cout << "Status vize uspijesno promijenjen" << endl;
//	else
//		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
//
//
//	if (jasmin.DodajStatus(&poslovna, PONISTENA, "predstavnicima kompanije Microsoft nemaju informaciju o posjeti navedenog aplikanta"))
//		cout << "Status vize uspijesno promijenjen" << endl;
//	else
//		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
//
//	TuristickaViza turisticka(ENGLESKA, dat18082017, dat11122017, "Whitehall Pl, London SW1A 2BD, UK");
//
//	/*if (jasmin.DodajStatus(&turisticka, ZAHTJEV_ZAPRIMLJEN))
//		cout << "Status vize uspijesno promijenjen" << endl;
//	else
//		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;*/
//
//	//if (jasmin.DodajStatus(&turisticka, IZDATA)) {
//	//	cout << "Status vize uspijesno promijenjen" << endl;
//	//	//U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
//	//	jasmin.PrintajVizu(&turisticka);
//	//}
//	//else
//	//	cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
//	////VRAĆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREĐENU DRŽAVU, A KOJE SU IMALE ODREĐENI STATUS
//	//vector<Viza*> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);
//
//	////UNUTAR NAPOMENE MIJENJA SADRŽAJ "nemaju informaciju" SA "su upoznti sa" - KORISTITI REGEX
//	//jasmin.ZamijeniRijec("nemaju informaciju", "su upoznti sa");
//
//	system("pause");
//}
//
//
//
//
//
//
//
//
//
//
//



























































































//#include<iostream>
//#include<string>
//#include<vector>
//#include<sstream>
//#include<regex>
//#include<thread>
//#include<mutex>
//#include<iterator>
//
//using namespace std;
//mutex m;
//const char* crt = "\n-------------------------------------------\n";
//enum GodinaStudija { PRVA = 1, DRUGA, TRECA };
//
//char* Alociraj(const char* sadrzaj) {
//	if (sadrzaj == nullptr)return nullptr;
//	int vel = strlen(sadrzaj) + 1;
//	char* temp = new char[vel];
//	strcpy_s(temp, vel, sadrzaj);
//	return temp;
//}
//
//template<class T1, class T2>
//class Dictionary {
//	T1* _elementi1;
//	T2* _elementi2;
//	int* _trenutno;
//public:
//	Dictionary() {
//		_elementi1 = nullptr;
//		_elementi2 = nullptr;
//		_trenutno = new int(0);
//	}
//	~Dictionary() {
//		delete[]_elementi1; _elementi1 = nullptr;
//		delete[]_elementi2; _elementi2 = nullptr;
//		delete _trenutno; _trenutno = nullptr;
//	}
//	Dictionary(const Dictionary& obj)
//	{
//		_trenutno = new int(*obj._trenutno);
//		_elementi1 = new T1[*_trenutno];
//		_elementi2 = new T2[*_trenutno];
//		for (size_t i = 0; i < *_trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//	}
//	Dictionary& operator=(const Dictionary& obj)
//	{
//		if (&obj == this)
//		{
//			return *this;
//		}
//		_trenutno = new int(*obj._trenutno);
//		_elementi1 = new T1[*_trenutno];
//		_elementi2 = new T2[*_trenutno];
//		for (size_t i = 0; i < *_trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//		return *this;
//	}
//	void AddElement(const T1& element1, const T2& element2)
//	{
//		T1* temp1 = new T1[*_trenutno + 1];
//		T2* temp2 = new T2[*_trenutno + 1];
//		for (size_t i = 0; i < *_trenutno; i++)
//		{
//			temp1[i] = _elementi1[i];
//			temp2[i] = _elementi2[i];
//		}
//		delete[]_elementi1;
//		delete[]_elementi2;
//		_elementi1 = temp1;
//		_elementi2 = temp2;
//		_elementi1[*_trenutno] = element1;
//		_elementi2[*_trenutno] = element2;
//		(*_trenutno)++;
//	}
//	Dictionary<T1, T2>getRange(int i, int j)
//	{
//		if (i > j) { throw exception("Prva lokacija ne smije biti manja od druge"); }
//		if (i<0 || j> * _trenutno) { throw exception("Nepostojeca lokacija"); }
//		Dictionary<T1, T2> temp;
//		for (size_t k = i; k < j; k++)
//		{
//			temp.AddElement(_elementi1[k], _elementi2[k]);
//		}
//		return temp;
//	}
//	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
//	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
//	int getTrenutno() { return *_trenutno; }
//	friend ostream& operator<< (ostream& COUT, const Dictionary& obj) {
//		for (size_t i = 0; i < *obj._trenutno; i++)
//			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
//		return COUT;
//	}
//};
//class DatumVrijeme {
//	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
//public:
//	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
//		_dan = new int(dan);
//		_mjesec = new int(mjesec);
//		_godina = new int(godina);
//		_sati = new int(sati);
//		_minuti = new int(minuti);
//	}
//	DatumVrijeme(const DatumVrijeme& obj)
//	{
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		_sati = new int(*obj._sati);
//		_minuti = new int(*obj._minuti);
//	}
//	DatumVrijeme& operator=(const DatumVrijeme& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		_sati = new int(*obj._sati);
//		_minuti = new int(*obj._minuti);
//			return *this;
//	}
//	~DatumVrijeme() {
//		delete _dan; _dan = nullptr;
//		delete _mjesec; _mjesec = nullptr;
//		delete _godina; _godina = nullptr;
//		delete _sati; _sati = nullptr;
//		delete _minuti; _minuti = nullptr;
//	}
//	char* ToCharArray() {
//		stringstream ss;
//		if (*_dan<10 && *_mjesec<10)
//		{
//			ss << "0" << *_dan << "/" <<"0"<< *_mjesec << "/" << *_godina << " " << *_sati << ":" << *_minuti << endl;
//		}
//		if (*_dan<10 && *_mjesec>10)
//		{
//			ss << "0" << *_dan << "/"<< *_mjesec << "/" << *_godina << " " << *_sati << ":" << *_minuti << endl;
//		}
//		if (*_dan>10 && *_mjesec>10)
//		{
//			ss << *_dan << "/"<< *_mjesec << "/" << *_godina << " " << *_sati << ":" << *_minuti << endl;
//		}
//		if (*_dan>10 && *_mjesec<10)
//		{
//			ss << *_dan << "/"<<"0"<< *_mjesec << "/" << *_godina << " " << *_sati << ":" << *_minuti << endl;
//		}
//		return Alociraj(ss.str().c_str());
//	}
//	int toMinute() {
//		return *_dan * 24 * 60 + *_mjesec * 30 * 24 * 60 + *_godina * 365 * 24 * 60 + *_sati * 60 + *_minuti;
//	}
//	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
//		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
//		return COUT;
//	}
//};
//
//class Predmet {
//	char* _naziv;
//	int _ocjena;
//	string _napomena;
//public:
//	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
//		_naziv = Alociraj(naziv);
//		_ocjena = ocjena;
//		_napomena = napomena;
//	}
//	~Predmet() {
//		delete[] _naziv; _naziv = nullptr;
//	}
//	Predmet(const Predmet& obj)
//	{
//		_naziv = Alociraj(obj._naziv);
//		_ocjena = obj._ocjena;
//		_napomena = obj._napomena;
//	}
//	Predmet& operator=(const Predmet& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_naziv = Alociraj(obj._naziv);
//		_ocjena = obj._ocjena;
//		_napomena = obj._napomena;
//			return *this;
//	}
//	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
//		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
//		return COUT;
//	}
//	string GetNapomena() { return _napomena; }
//	char* GetNaziv() { return _naziv; }
//	int GetOcjena() { return _ocjena; }
//
//	void DodajNapomenu(string napomena) {
//		_napomena += " " + napomena;
//	}
//};
//class Uspjeh {
//	GodinaStudija* _godina;
//	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
//	Dictionary<Predmet, DatumVrijeme> _predmeti;
//public:
//	Uspjeh(GodinaStudija godina) {
//		_godina = new GodinaStudija(godina);
//	}
//	~Uspjeh() { delete _godina; _godina = nullptr; }
//	Uspjeh(const Uspjeh & obj)
//	{
//		_godina = new GodinaStudija(*obj._godina);
//		_predmeti = obj._predmeti;
//	}
//	Uspjeh& operator=(const Uspjeh & obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_godina = new GodinaStudija(*obj._godina);
//		_predmeti = obj._predmeti;
//			return *this;
//	}
//	Dictionary<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
//	GodinaStudija* GetGodinaStudija() { return _godina; }
//	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
//		COUT << *obj._godina << " " << obj._predmeti << endl;
//		return COUT;
//	}
//};
//
//class Student {
//	char* _imePrezime;
//	string _emailAdresa;
//	string _brojTelefona;
//	vector<Uspjeh> _uspjeh;
//	bool isValidanEmail(string email)
//	{
//		regex pravilo("\\w*\\.\\w*\\@(hotmail.com|outlook.com|fit.ba)");
//		return regex_match(email, pravilo);
//	}
//public:
//	Student(const char* imePrezime, string emailAdresa, string brojTelefona) {
//		_imePrezime = Alociraj(imePrezime);
//		_emailAdresa = isValidanEmail(emailAdresa) ? emailAdresa : " notSet@fit.ba";
//			
//		_brojTelefona = brojTelefona;
//	}
//	~Student() {
//		delete[] _imePrezime; _imePrezime = nullptr;
//	}
//	Student(const Student&obj)
//	{
//		_imePrezime = Alociraj(obj._imePrezime);
//		_emailAdresa = obj._emailAdresa;
//		_brojTelefona = obj._brojTelefona;
//		for (size_t i = 0; i < obj._uspjeh.size(); i++)
//		{
//			_uspjeh.push_back(obj._uspjeh[i]);
//		}
//	}
//	Student& operator=(const Student& obj)
//	{
//		if (&obj == this)
//		{
//			return *this;
//		}
//		_imePrezime = Alociraj(obj._imePrezime);
//		_emailAdresa = obj._emailAdresa;
//		_brojTelefona = obj._brojTelefona;
//		for (size_t i = 0; i < obj._uspjeh.size(); i++)
//		{
//			_uspjeh.push_back(obj._uspjeh[i]);
//		}
//		return *this;
//	}
//	bool AddPredmet(Predmet& predmet, GodinaStudija gs, DatumVrijeme& datumVrijeme)
//	{
//		for (vector<Uspjeh>::iterator uspjeh = _uspjeh.begin(); uspjeh != _uspjeh.end(); uspjeh++)
//		{
//			if (*uspjeh->GetGodinaStudija() == gs)
//			{
//				for (size_t i = 0; i < uspjeh->GetPredmeti()->getTrenutno(); i++)
//				{
//					if (strcmp(uspjeh->GetPredmeti()->getElement1(i).GetNaziv(), predmet.GetNaziv()) == 0)
//					{
//						cout << "Vec postoji taj predmet" << endl;
//						return false;
//					}
//					if (datumVrijeme.toMinute() - uspjeh->GetPredmeti()->getElement2(i).toMinute() < 60)
//					{
//						cout << "Nije prosao sat od posljednjeg dodavanja" << endl;
//						return false;
//					}
//				}
//			}
//		}
//		Uspjeh uspjeh(gs);
//		uspjeh.GetPredmeti()->AddElement(predmet, datumVrijeme);
//		_uspjeh.push_back(uspjeh);
//		/*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije AddPredmet, Studentu se salje email sa sadrzajem:
//	FROM:info@fit.ba
//	TO: emailStudenta
//	Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
//	Pozdrav.
//	FIT Team.
//	ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X ostvaren u X godini studija".
//	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
//	*/
//		thread email([&]() {
//			m.lock();
//			cout << "FROM:info@fit.ba" << endl << "TO: " << _emailAdresa << endl
//				<< "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << gs << " godinu studija." << endl << "Pozdrav.FIT Team. " << endl;
//			m.unlock();
//			});
//		if (prosjecna(gs) > 8.0)
//		{
//			thread sms([&] {
//			m.lock();
//				cout << "Svaka cast za uspjeh " << prosjecna(gs) << " ostvaren u " << gs << " godini studija" << endl;
//			m.unlock();
//				});
//			sms.join();
//		}
//		email.join();
//		return true;
//
//	}
//	friend ostream& operator<< (ostream& COUT, Student& obj) {
//		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
//		ostream_iterator<Uspjeh> o_it(COUT, crt);
//		copy(obj._uspjeh.begin(), obj._uspjeh.end(), o_it);
//		return COUT;
//	}
//	int BrojPonavljanjaRijeci(string rijec)
//	{
//		int brojPonavljanja = 0;
//		for (size_t i = 0; i < _uspjeh.size(); i++)
//		{
//			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
//			{
//				regex pravilo(rijec);
//				string napomene = _uspjeh[i].GetPredmeti()->getElement1(j).GetNapomena();
//				auto start = sregex_iterator(napomene.begin(), napomene.end(),pravilo);
//				auto end = sregex_iterator();
//				brojPonavljanja += distance(start, end);
//			}
//		}
//		return brojPonavljanja;
//	}
//	vector<Predmet> operator()(DatumVrijeme *datum1, DatumVrijeme* datum2)
//	{
//		vector<Predmet> predmeti;
//		for (size_t i = 0; i < _uspjeh.size(); i++)
//		{
//			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
//			{
//				if (_uspjeh[i].GetPredmeti()->getElement2(j).toMinute()>datum1->toMinute() && _uspjeh[i].GetPredmeti()->getElement2(j).toMinute()<datum2->toMinute())
//				{
//					predmeti.push_back(_uspjeh[i].GetPredmeti()->getElement1(j));
//				}
//			}
//		}
//		return predmeti;
//	}
//	Uspjeh* operator[](string godina) {
//		for (int i = 0; i < _uspjeh.size(); i++) {
//			if (godina == "PRVA" && *_uspjeh[i].GetGodinaStudija() == PRVA) return &_uspjeh[i];
//			if (godina == "DRUGA" && *_uspjeh[i].GetGodinaStudija() == DRUGA) return &_uspjeh[i];
//			if (godina == "TRECA" && *_uspjeh[i].GetGodinaStudija() == TRECA) return &_uspjeh[i];
//		}
//		return nullptr;
//	}
//	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
//	string GetEmail() { return _emailAdresa; }
//	string GetBrojTelefona() { return _brojTelefona; }
//	float prosjecna(GodinaStudija gs) {
//		float prosjecna = 0;
//		int brojac = 0;
//		for (size_t i = 0; i < _uspjeh.size(); i++)
//		{
//			if (*_uspjeh[i].GetGodinaStudija() == gs)
//			{
//				for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
//				{
//					prosjecna += _uspjeh[i].GetPredmeti()->getElement1(j).GetOcjena();
//					brojac++;
//				}
//			}
//		}
//		return prosjecna /= brojac;
//	}
//	char* GetImePrezime() { return _imePrezime; }
//};
//
//void main() {
//	/****************************************************************************
//	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
//	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
//	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
//	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
//	****************************************************************************/
//	//cout << "NA KRAJU ISPITA, RAD PREDAJTE U ODGOVARAJUCI FOLDER NA FTP SERVERU (INTEGRALNI)!" << endl;
//	DatumVrijeme temp,
//		datum19062019_1015(19, 6, 2019, 10, 15),
//		datum20062019_1115(20, 6, 2019, 11, 15),
//		datum30062019_1215(30, 6, 2019, 12, 15),
//		datum05072019_1231(5, 7, 2019, 12, 31);
//	//funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
//	//voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca iskazane kao dvije cifre
//	cout << datum19062019_1015.ToCharArray() << endl;//treba ispisati: 19/06/2019 10:15
//	temp = datum05072019_1231;
//	cout << temp.ToCharArray() << endl;//treba ispisati: 05/07/2019 12:31
//
//	const int DictionaryTestSize = 9;
//	Dictionary<int, int> Dictionary1;
//	for (size_t i = 0; i < DictionaryTestSize; i++)
//		Dictionary1.AddElement(i + 1, i * i);
//
//	try {
//		//vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
//		//funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost posljednje lokacije manja od pocetne
//		Dictionary<int, int> opseg = Dictionary1.getRange(2, 7);
//		cout << opseg << endl;
//		Dictionary1.getRange(7, 11);
//	}
//	catch (exception & err) {
//		cout << err.what() << endl;
//	}
//	cout << Dictionary1 << endl;
//
//	Dictionary<int, int> Dictionary2 = Dictionary1;
//	cout << Dictionary2 << crt;
//
//	Dictionary<int, int> Dictionary3;
//	Dictionary3 = Dictionary1;
//	cout << Dictionary3 << crt;
//
//	//napomena se moze dodati i prilikom kreiranja objekta
//	Predmet MAT("Matematika", 7, "Ucesce na takmicenju"),
//		UIT("Uvod u informacijske tehnologije", 9),
//		RM("Racunarske mreze", 8),
//		EN("Engleski jezik", 6);
//	UIT.DodajNapomenu("Pohvala za ostvareni uspjeh");
//	cout << MAT << endl;
//
//	/*
//	email adresa mora biti u formatu: text-text@ nakon cega slijedi neka od sljedecih domena: hotmail.com ili outlook.com ili fit.ba. 
//	Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
//	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
//	za provjeru koristiti regex
//	*/
//	Student jasmin("Jasmin Azemovic", "jasmin.azemovic@hotmail.com", "033 281 172");
//	Student adel("Adel Handzic", "adel.handzic@fit.ba", "033 281 170");
//	Student emailNotValid("Ime Prezime", "korisnik@lazna.ba", "033 281 170");
//
//	/*
//	uspjeh se dodaje za svaki predmet na nivou godine studija.
//	tom prilikom onemoguciti:
//	- dodavanje istoimenih predmeta na nivou jedne godine,
//	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 1 sat).
//	godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za drugu godinu, pa onda za prvu godinu i sl.).
//	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
//	*/
//	if (jasmin.AddPredmet(UIT, DRUGA, datum20062019_1115))
//		cout << "Predmet uspjesno dodan!" << crt;
//	if (jasmin.AddPredmet(RM, DRUGA, datum30062019_1215))
//		cout << "Predmet uspjesno dodan!" << crt;
//	if (jasmin.AddPredmet(EN, PRVA, datum19062019_1015))
//		cout << "Predmet uspjesno dodan!" << crt;
//	if (jasmin.AddPredmet(MAT, PRVA, datum20062019_1115))
//		cout << "Predmet uspjesno dodan!" << crt;
//	//ne treba dodati MAT jer je vec dodana u prvoj godini
//	if (jasmin.AddPredmet(MAT, PRVA, datum05072019_1231))
//		cout << "Predmet uspjesno dodan!" << crt;
//	//ne treba dodati UIT jer nije prosao 1 sat od dodavanja posljednjeg predmeta
//	if (jasmin.AddPredmet(UIT, PRVA, datum20062019_1115))
//		cout << "Predmet uspjesno dodan!" << crt;
//
//	/*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije AddPredmet, Studentu se salje email sa sadrzajem:
//	FROM:info@fit.ba
//	TO: emailStudenta
//	Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
//	Pozdrav.
//	FIT Team.
//	ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X ostvaren u X godini studija".
//	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
//	*/
//
//	cout << "USPJEH ISPISATI KORISTEĆI OSTREAM_ITERATOR" << endl;
//	cout << jasmin << endl;
//	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
//	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;
//
//	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
//	vector<Predmet> jasminUspjeh = jasmin(new DatumVrijeme(18, 06, 2019, 10, 15), new DatumVrijeme(21, 06, 2019, 10, 10));
//	for (Predmet u : jasminUspjeh)
//		cout << u << endl;
//
//	cout << crt << crt << endl;
//
//	Uspjeh * uspjeh_I_godina = jasmin["PRVA"];//vraca uspjeh Studenta ostvaren u prvoj godini studija
//	if (uspjeh_I_godina != nullptr)
//		cout << *uspjeh_I_godina << endl;
//
//	//cin.get();
//	system("pause");
//}





















































































































//#include<iostream>
//#include<vector>
//#include<string>
//#include<sstream>
//#include<thread>
//#include<mutex>
//using namespace std;
//
///****************************************************************************
//1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
//3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
//4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
//****************************************************************************/
//
//const char* crt = "\n-------------------------------------------\n";
//const char* nedozvoljena_operacija = "Nedozvoljena operacija";
//const char* not_set = "NOT_SET";
//const int min_polgavlja = 3;
//const int min_karaktera_po_poglavlju = 30;
//mutex m;
//
//char* AlocirajNizKaraktera(const char* sadrzaj) {
//	if (sadrzaj == nullptr)
//		return nullptr;
//	int vel = strlen(sadrzaj) + 1;
//	char* temp = new char[vel];
//	strcpy_s(temp, vel, sadrzaj);
//	return temp;
//}
//
//template<class T1, class T2>
//class Kolekcija {
//	T1* _elementi1;
//	T2* _elementi2;
//	int _trenutno;
//public:
//	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
//	~Kolekcija() {
//		delete[] _elementi1; _elementi1 = nullptr;
//		delete[] _elementi2; _elementi1 = nullptr;
//	}
//	Kolekcija(const Kolekcija& obj)
//	{
//		_elementi1 = new T1[obj._trenutno];
//		_elementi2 = new T2[obj._trenutno];
//		for (size_t i = 0; i < obj._trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//		_trenutno = obj._trenutno;
//	}
//	Kolekcija& operator=(const Kolekcija& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_elementi1 = new T1[obj._trenutno];
//		_elementi2 = new T2[obj._trenutno];
//		for (size_t i = 0; i < obj._trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//		_trenutno = obj._trenutno;
//			return *this;
//	}
//	void DodajElement(const T1& element1, const T2& element2)
//	{
//		T1* temp1 = new T1[_trenutno + 1];
//		T2* temp2 = new T2[_trenutno + 1];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			temp1[i] = _elementi1[i];
//			temp2[i] = _elementi2[i];
//		}
//		delete[]_elementi1;
//		delete[]_elementi2;
//		_elementi1 = temp1;
//		_elementi2 = temp2;
//		_elementi1[_trenutno] = element1;
//		_elementi2[_trenutno] = element2;
//		_trenutno++;
//	}
//	T1* getElementi1Pok() { return _elementi1; }
//	T2* getElementi2Pok() { return _elementi2; }
//	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
//	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
//	int getTrenutno() { return _trenutno; }
//
//	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
//		for (size_t i = 0; i < obj._trenutno; i++)
//			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
//		return COUT;
//	}
//};
//class Poglavlje {
//	char* _naslov;
//	char* _sadrzaj;
//	bool _prihvaceno;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
//	int _ocjena;
//public:
//	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
//		:_ocjena(0), _prihvaceno(false) {
//		_naslov = AlocirajNizKaraktera(naslov);
//		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
//	}
//	Poglavlje() {
//		delete[] _naslov; _naslov = nullptr;
//		delete[] _sadrzaj; _sadrzaj = nullptr;
//	}
//	Poglavlje(const Poglavlje& obj)
//	{
//		_naslov = AlocirajNizKaraktera(obj._naslov);
//		_sadrzaj = AlocirajNizKaraktera(obj._sadrzaj);
//		_prihvaceno = obj._prihvaceno;
//		_ocjena = obj._ocjena;
//	}
//	Poglavlje& operator=(const Poglavlje& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_naslov = AlocirajNizKaraktera(obj._naslov);
//		_sadrzaj = AlocirajNizKaraktera(obj._sadrzaj);
//		_prihvaceno = obj._prihvaceno;
//		_ocjena = obj._ocjena;
//			return *this;
//	}
//	friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
//		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
//			return COUT;
//		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
//		if (obj._prihvaceno)
//			COUT << "Ocjena: " << obj._ocjena << endl;;
//		return COUT;
//	}
//	char* GetNaslov() { return _naslov; }
//	char* GetSadrzaj() { return _sadrzaj; }
//	bool GetPrihvaceno() { return _prihvaceno; }
//	void SetPrihvaceno() { _prihvaceno = true; }
//	void promjeniSadrzaj(const char* noviSadrzaj)
//	{
//		if (noviSadrzaj==nullptr)
//		{
//			return;
//		}
//		stringstream ss;
//		ss << _sadrzaj << " " << noviSadrzaj;
//		delete[]_sadrzaj; _sadrzaj = nullptr;
//		_sadrzaj = AlocirajNizKaraktera( ss.str().c_str());
//	}
//	int GetOcjena() { return _ocjena; }
//	void SetOcjena(int ocjena) {
//		_ocjena = ocjena;
//	}
//};
//
//class ZavrsniRad {
//	char* _tema;
//	vector<Poglavlje> _poglavljaRada;
//	string _datumOdbrane;
//	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
//public:
//	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
//		_tema = AlocirajNizKaraktera(nazivTeme);
//	}
//
//	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
//		_tema = AlocirajNizKaraktera(org._tema);
//	}
//	ZavrsniRad& operator=(const ZavrsniRad& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_tema = AlocirajNizKaraktera(obj._tema);
//		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
//		{
//			_poglavljaRada.push_back(obj._poglavljaRada[i]);
//		}
//		_datumOdbrane = obj._datumOdbrane;
//		_konacnaOcjena = obj._konacnaOcjena;
//		return *this;
//	}
//
//
//	~ZavrsniRad() {
//		delete[] _tema; _tema = nullptr;
//	}
//	char* GetNazivTeme()const { return _tema; }
//	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
//	string GetDatumOdbrane()const { return _datumOdbrane; }
//	float GetOcjena() { return _konacnaOcjena; }
//	void SetDatumOdbrane(string datumOdbrane) { _datumOdbrane = datumOdbrane; }
//	void DodajPoglavlje(const char* nazivPoglavlja, const char* sadrzajPoglavlja)
//	{
//		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i < _poglavljaRada.end(); i++)
//		{
//			if (strcmp(i->GetNaslov(),nazivPoglavlja)==0)
//			{
//				i->promjeniSadrzaj(sadrzajPoglavlja);
//				return;
//			}
//		}
//		_poglavljaRada.push_back(Poglavlje(nazivPoglavlja, sadrzajPoglavlja));
//	}
//	void OcijeniPoglavlje(const char* nazivPoglavlja, int ocjena) {
//		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i < _poglavljaRada.end(); i++)
//		{
//			if (strcmp(i->GetNaslov(), nazivPoglavlja) == 0)
//			{
//				if (ocjena >=6 && ocjena <=10)
//				{
//					i->SetOcjena(ocjena);
//					i->SetPrihvaceno();
//					return;
//				}
//				else
//				{
//					throw exception("Ocjena nije pozitivna");
//				}
//			}
//		}
//		throw exception("Poglavlje ne postoji");
//	}
//	bool operator==(const ZavrsniRad& zavrsniRad) {
//		return strcmp(_tema, zavrsniRad.GetNazivTeme()) == 0;
//	}
//	void SetKonacnuOcjenu(float konacnaOcjena) { _konacnaOcjena = konacnaOcjena; }
//	float prosjecnaOcjena() {
//		float prosjecna = 0;
//		int brojac = 0;
//		for (size_t i = 0; i < _poglavljaRada.size(); i++)
//		{
//			if (_poglavljaRada[i].GetOcjena() >= 6 && _poglavljaRada[i].GetOcjena() <= 10)
//			{
//				brojac++;
//				prosjecna += _poglavljaRada[i].GetOcjena();
//			}
//		}
//		return prosjecna /= brojac;
//	}
//	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
//		COUT << "Tema rada: " << obj._tema << endl;
//		COUT << "Sadrzaj: " << endl;
//		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
//			COUT << obj._poglavljaRada[i] << endl;
//		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
//		return COUT;
//	}
//};
//
//class Osoba {
//protected:
//	string _imePrezime;
//public:
//	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
//	string GetImePrezime() { return _imePrezime; }
//	virtual void Info() = 0;
//};
//
//class Nastavnik :public Osoba {
//	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
//	Kolekcija<string, ZavrsniRad> _teme;
//public:
//	Nastavnik(string imePrezime):Osoba(imePrezime)
//	{}
//	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
//	bool DodajZavrsniRad(string indeks,const ZavrsniRad& zavrsniRad)
//	{
//		for (size_t i = 0; i < _teme.getTrenutno(); i++)
//		{
//			if (_teme.getElement2(i)== zavrsniRad)
//			{
//				cout << "Vec postoji taj rad " << endl;
//				return false;
//			}
//			if (_teme.getElement1(i)== indeks)
//			{
//				cout << "Rad vec dodan studentu sa ovim brojem indeksa" << endl;
//				return false;
//			}
//		}
//		_teme.DodajElement(indeks, zavrsniRad);
//		return true;
//	}
//	ZavrsniRad* ZakaziOdbranuRada(string indeks, string datumOdbrane)
//	{
//		for (size_t i = 0; i < _teme.getTrenutno(); i++)
//		{
//			if (_teme.getElement1(i) == indeks)
//			{
//				if (_teme.getElement2(i).GetPoglavlja().size()>min_polgavlja)
//				{
//					for (size_t j = 0; j < _teme.getElement2(i).GetPoglavlja().size(); j++)
//					{
//						if (strlen(_teme.getElement2(i).GetPoglavlja()[j].GetSadrzaj())>min_karaktera_po_poglavlju)
//						{
//							if (_teme.getElement2(i).GetPoglavlja()[j].GetPrihvaceno())
//							{
//								_teme.getElement2(i).SetDatumOdbrane(datumOdbrane);
//								_teme.getElement2(i).SetKonacnuOcjenu(_teme.getElement2(i).prosjecnaOcjena());
//								ZavrsniRad* temp = new ZavrsniRad(_teme.getElement2(i));
//								return temp;
//							}
//						}
//					}
//				}
//			}
//		}
//		return nullptr;
//	}
//	void Info() {
//		cout << crt;
//		cout << "Ime nastavnika: " << _imePrezime << endl;
//		cout << "Mentorstva: " << endl;
//		cout << _teme << endl;
//		cout << crt;
//	};
//};
//
//
//string PosaljiPozivZaDodjeluNagrada(Nastavnik* nastavnici[], int brojNastavnika, float trazeniProsjek)
//{
//	stringstream ss;
//	for (size_t i = 0; i < brojNastavnika; i++)
//	{
//		for (size_t j = 0; j < nastavnici[i]->GetTeme().getTrenutno(); j++)
//		{
//			if (nastavnici[i]->GetTeme().getElement2(j).GetOcjena() > trazeniProsjek)
//			{
//				thread email([&] {
//					m.lock();
//					ss << "Postovani " << nastavnici[i]->GetTeme().getElement1(j)
//						<< " uzimajuci u obzir cinjenicu da ste kod mentora " << nastavnici[i]->GetImePrezime() << " uspjesno odbranili rad sa ocjenom "
//						<< nastavnici[i]->GetTeme().getElement2(j).GetOcjena()
//						<< " cast nam je pozvati Vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT - u 03.07.2019.godine." << endl;
//					m.unlock();
//					});
//				email.join();
//			}
//		}
//
//	}
//	return ss.str();
//}
//
//
//int main() {
//	//cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
//	//cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;
//
//	const int max = 4;
//	Nastavnik* nastavnici[max];
//
//	nastavnici[0] = new Nastavnik("Denis Music");
//	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
//	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
//	nastavnici[3] = new Nastavnik("Emina Junuz");
//	//parametri: naziv zavrsnog rada
//	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
//	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
//	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežičnih računarskih mreža");
//	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih ključeva");
//
//	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj 
//	i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzajem*/
//	//parametri: nazivPoglavlja, sadrzajPoglavlja
//	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
//	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
//	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
//	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
//	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
//	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");
//
//	//cout << multimedijalni << endl;
//
//	try {
//		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja,dodjeljuje ocjenu poglavlju te 
//		ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim.
//		U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
//		//parametri:nazivPoglavlja, ocjena
//
//		multimedijalni.OcijeniPoglavlje("Uvod", 8);
//		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
//		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
//		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
//		multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
//	}
//	catch (exception & err) {
//		cout << "Greska -> " << err.what() << endl;
//	}
//	//cout << multimedijalni << endl;
//
//	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. 
//	zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
//	sprijeciti dodavanje zavrsnih radova sa istom temom*/
//	//parametri: brojIndeksa, zavrsniRad
//	if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
//		cout << "Zavrsni rad uspjesno dodat!" << endl;
//	if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
//		cout << "Zavrsni rad uspjesno dodat!" << endl;
//	if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
//		cout << "Zavrsni rad nije dodat!" << endl;
//	if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
//		cout << "Zavrsni rad nije dodat!" << endl;
//	if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
//		cout << "Zavrsni rad uspjesno dodat!" << endl;
//	if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
//		cout << "Zavrsni rad uspjesno dodat!" << endl;
//
//	cout << crt << crt;
//
//	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
//	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
//		1. zavrsni rad ima broj poglavlja veci od minimalnog
//		2. svako poglavlje ima broj karaktera veci od minimalnog
//		3. svako poglavlje je prihvaceno/odobreno
//	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
//	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.*/
//
//
////parametri: brojIndeksa, datumOdbrane
//	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
//	if (zr1 != nullptr)
//		cout << *zr1 << endl;
//
//	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
//	if (zr1 != nullptr)
//		cout << *zr1 << endl;
//
//	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
//	nastavnici[0]->Info();
//	nastavnici[1]->Info();
//	nastavnici[2]->Info();
//	nastavnici[3]->Info();
//
//	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
//	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
//	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati Vas na 
//	dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine."	.
//	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
//	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 7) << endl;
//
//	for (int i = 0; i < max; i++) {
//		delete nastavnici[i];
//		nastavnici[i] = nullptr;
//	}
//	system("pause");
//	return 0;
//}



//
//#include<iostream>
//#include<vector>
//#include<string>
//#include<sstream>
//#include<exception>
//using namespace std;
//
///****************************************************************************
//1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
//3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
//4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
//****************************************************************************/
//
//const char* crt = "\n-------------------------------------------\n";
//const char* nedozvoljena_operacija = "Nedozvoljena operacija";
//const char* not_set = "NOT_SET";
//const int min_polgavlja = 3;
//const int min_karaktera_po_poglavlju = 30;
//
//char* AlocirajNizKaraktera(const char* sadrzaj) {
//	if (sadrzaj == nullptr)
//		return nullptr;
//	int vel = strlen(sadrzaj) + 1;
//	char* temp = new char[vel];
//	strcpy_s(temp, vel, sadrzaj);
//	return temp;
//}
//
//template<class T1, class T2>
//class Kolekcija {
//	T1* _elementi1;
//	T2* _elementi2;
//	int _trenutno;
//public:
//	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
//	~Kolekcija() {
//		delete[] _elementi1; _elementi1 = nullptr;
//		delete[] _elementi2; _elementi1 = nullptr;
//	}
//	Kolekcija(const Kolekcija& obj)
//	{
//		_trenutno = obj._trenutno;
//		_elementi1 = new T1[_trenutno];
//		_elementi2 = new T2[_trenutno];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//	}
//	Kolekcija& operator=(const Kolekcija& obj)
//	{
//		if (&obj == this)
//		{
//			return *this;
//		}
//		delete[] _elementi1; _elementi1 = nullptr;
//		delete[] _elementi2; _elementi1 = nullptr;
//		_trenutno = obj._trenutno;
//		_elementi1 = new T1[_trenutno];
//		_elementi2 = new T2[_trenutno];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//		return *this;
//	}
//
//	void addElement(const T1& elem1, const T2& elem2) {
//		T1* temp1 = new T1[_trenutno + 1];
//		T2* temp2 = new T2[_trenutno + 1];
//
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			temp1[i] = _elementi1[i];
//			temp2[i] = _elementi2[i];
//		}
//
//		delete[]_elementi1;
//		delete[]_elementi2;
//
//		_elementi1[_trenutno] = elem1;
//		_elementi2[_trenutno] = elem2;
//		_trenutno++;
//	}
//
//	T1* getElementi1Pok() { return _elementi1; }
//	T2* getElementi2Pok() { return _elementi2; }
//	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
//	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
//	int getTrenutno() { return _trenutno; }
//
//	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
//		for (size_t i = 0; i < obj._trenutno; i++)
//			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
//		return COUT;
//	}
//};
//class Poglavlje {
//	char* _naslov;
//	char* _sadrzaj;
//	bool _prihvaceno;
//	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
//public:
//	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
//		:_ocjena(0), _prihvaceno(false) {
//		_naslov = AlocirajNizKaraktera(naslov);
//		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
//	}
//	Poglavlje() {
//		delete[] _naslov; _naslov = nullptr;
//		delete[] _sadrzaj; _sadrzaj = nullptr;
//	}
//	friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
//		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
//			return COUT;
//		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
//		if (obj._prihvaceno)
//			COUT << "Ocjena: " << obj._ocjena << endl;;
//		return COUT;
//	}
//
//	void SetOcjena(int ocjena)
//	{
//		_ocjena = ocjena;
//	}
//
//	void SetPrihvaceno(bool prihvaceno)
//	{
//		_prihvaceno = prihvaceno;
//	}
//
//	void dodajSadrzaj(const char* sadrzaj) {
//		char* temp = AlocirajNizKaraktera(_sadrzaj);
//		if (_sadrzaj != nullptr)
//		{
//			delete[]_sadrzaj; _sadrzaj = nullptr;
//		}
//		stringstream ss;
//		ss << temp << " " << sadrzaj << " ";
//		_sadrzaj = AlocirajNizKaraktera(ss.str().c_str());
//	}
//
//	char* GetNaslov() { return _naslov; }
//	char* GetSadrzaj() { return _sadrzaj; }
//	bool GetPrihvaceno() { return _prihvaceno; }
//	int GetOcjena() { return _ocjena; }
//};
//
//class ZavrsniRad {
//	char* _tema;
//	vector<Poglavlje> _poglavljaRada;
//	string _datumOdbrane;
//	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
//public:
//	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
//		_tema = AlocirajNizKaraktera(nazivTeme);
//	}
//
//	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
//		_tema = AlocirajNizKaraktera(org._tema);
//	}
//
//	ZavrsniRad& operator=(const ZavrsniRad& org) {
//		if (&org == this) {
//			return *this;
//		}
//		_poglavljaRada = org._poglavljaRada;
//		_konacnaOcjena = org._konacnaOcjena;
//		_datumOdbrane = org._datumOdbrane;
//		delete[] _tema; _tema = nullptr;
//		_tema = AlocirajNizKaraktera(org._tema);
//		return *this;
//	}
//
//	~ZavrsniRad() {
//		delete[] _tema; _tema = nullptr;
//	}
//	char* GetNazivTeme()const { return _tema; }
//	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
//	string GetDatumOdbrane()const { return _datumOdbrane; }
//
//	float GetOcjena() { return _konacnaOcjena; }
//	void SetDatumOdbrane(string datumOdbrane) { _datumOdbrane = datumOdbrane; }
//
//	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj.
//	ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju
//	treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor).
//	u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
//	void DodajPoglavlje(const char* nazivPoglavlja, const char* sadrzajPoglavlja) {
//		bool flag = true;
//
//		for (size_t i = 0; i < _poglavljaRada.size(); i++)
//		{
//			if (strcmp(_poglavljaRada[i].GetNaslov(), nazivPoglavlja) == 0)
//			{
//				_poglavljaRada[i].dodajSadrzaj(sadrzajPoglavlja);
//				flag = false;
//			}
//		}
//
//		if (!flag)
//		{
//			return;
//		}
//
//		_poglavljaRada.push_back(Poglavlje(nazivPoglavlja, sadrzajPoglavlja));
//	}
//
//	/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja,
//		dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10)
//		onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji,
//		funkcija baca izuzetak sa odgovarajucom porukom*/
//	void OcijeniPoglavlje(const char* naslovPoglavlja, int ocjena) {
//		if (ocjena < 1 || ocjena>10)
//		{
//			throw exception("Ocjena nije validna");
//		}
//		for (size_t i = 0; i < _poglavljaRada.size(); i++)
//		{
//			if (strcmp(_poglavljaRada[i].GetNaslov(), naslovPoglavlja) == 0)
//			{
//				_poglavljaRada[i].SetOcjena(ocjena);
//				if (ocjena >= 6 && ocjena <= 10)
//				{
//					_poglavljaRada[i].SetPrihvaceno(true);
//					return;
//				}
//			}
//		}
//
//		throw exception("Poglavlje ne postoji");
//	}
//
//	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
//		COUT << "Tema rada: " << obj._tema << endl;
//		COUT << "Sadrzaj: " << endl;
//		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
//			COUT << obj._poglavljaRada[i] << endl;
//		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
//		return COUT;
//	}
//};
//
//class Osoba {
//protected:
//	string _imePrezime;
//public:
//	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
//	string GetImePrezime() { return _imePrezime; }
//	virtual void Info() = 0 {
//		cout << "Ime i prezime: " << _imePrezime << endl;
//	};
//};
//
//class Nastavnik :public Osoba {
//	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
//	Kolekcija<string, ZavrsniRad> _teme;
//public:
//	Nastavnik(string imePrezime) :Osoba(imePrezime)
//	{}
//	void Info() {
//		Osoba::Info();
//		cout << "Teme: " << endl;
//		for (size_t i = 0; i < _teme.getTrenutno(); i++)
//		{
//			cout << _teme.getElement1(i) << "  " << _teme.getElement2(i) << endl;
//		}
//	}
//
//
//	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli
//	mentorstvo na zavrsnom radu.
//	zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
//	sprijeciti dodavanje zavrsnih radova sa istom temom*/
//	bool DodajZavrsniRad(string index, const ZavrsniRad& zavrsniRad) {
//		for (size_t i = 0; i < _teme.getTrenutno(); i++)
//		{
//			if (strcmp(_teme.getElement2(i).GetNazivTeme(), zavrsniRad.GetNazivTeme()) == 0 || _teme.getElement1(i) == index)
//			{
//				cout << "Vec postoji ova tema || Uceniku je vec dodijeljen rad" << endl;
//				return false;
//			}
//		}
//
//		_teme.addElement(index, zavrsniRad);
//		return true;
//	}
//
//	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
//	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
//		1. zavrsni rad ima broj poglavlja veci od minimalnog
//		2. svako poglavlje ima broj karaktera veci od minimalnog
//		3. svako poglavlje je prihvaceno/odobreno
//	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja),
//	postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
//	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih
//	kriterija nije zadovoljen, funkcija vraca nullptr.
//*/
//	ZavrsniRad* ZakaziOdbranuRada(string brojIndeksa, string datumOdbrane) {
//		for (size_t i = 0; i < _teme.getTrenutno(); i++)
//		{
//			if (_teme.getElement1(i) == brojIndeksa)
//			{
//				if (_teme.getElement2(i).GetPoglavlja().size() > 0)
//				{
//					for (size_t j = 0; j < _teme.getElement2(i).GetPoglavlja().size(); j++)
//					{
//						if (_teme.getElement2(i).GetPoglavlja()[j].GetPrihvaceno())
//						{
//							_teme.getElement2(i).SetDatumOdbrane(datumOdbrane);
//							//izracunajProsjecnu(i,j);
//							/*([&]()->float {
//								f
//							});*/
//							return &_teme.getElement2(i);
//						}
//					}
//				}
//			}
//		}
//		return nullptr;
//	}
//
//
//	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
//};
//
//int main() {
//	/*cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
//	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;*/
//
//
//	//info------> Skoro cijelo vrijeme sam radio bez mogucnosti da kompajliram,pitao sam i dezurne profesore da pokusaju rijesiti
//	//,error--->	LNK1168	cannot open C : \Users\ispit\source\repos\ispit\x64\Debug\ispit.exe for writing	ispit,iako nije bila otvorena 	konzola
//
//	const int max = 4;
//	Nastavnik* nastavnici[max];
//
//	nastavnici[0] = new Nastavnik("Denis Music");
//	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
//	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
//	nastavnici[3] = new Nastavnik("Emina Junuz");
//	//parametri: naziv zavrsnog rada
//	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
//	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
//	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežičnih računarskih mreža");
//	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih ključeva");
//
//	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj.
//	ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju
//	treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor).
//	u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
//
//	//parametri: nazivPoglavlja, sadrzajPoglavlja
//	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
//	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
//	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
//	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
//	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
//	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");
//
//	//tesitranje ispisa
//	//cout << multimedijalni << endl;
//	try {
//		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja,
//		dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10)
//		onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji,
//		funkcija baca izuzetak sa odgovarajucom porukom*/
//
//		//parametri:nazivPoglavlja, ocjena
//
//		multimedijalni.OcijeniPoglavlje("Uvod", 8);
//		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
//		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
//		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
//
//		//zakomentirano zbog toga sto linija prekida izvrsavanje daljeg koda
//		//multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
//	}
//	catch (exception & err) {
//		cout << "Greska -> " << err.what() << endl;
//	}
////
////	//tesitranje ispisa
////	cout << multimedijalni << endl;
////
////	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli
////	mentorstvo na zavrsnom radu.
////	zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
////	sprijeciti dodavanje zavrsnih radova sa istom temom*/
////
////	//parametri: brojIndeksa, zavrsniRad
////	if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
////		cout << "Zavrsni rad uspjesno dodat!" << endl;
////	if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
////		cout << "Zavrsni rad uspjesno dodat!" << endl;
////	if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
////		cout << "Zavrsni rad nije dodat!" << endl;
////	if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
////		cout << "Zavrsni rad nije dodat!" << endl;
////	if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
////		cout << "Zavrsni rad uspjesno dodat!" << endl;
////	if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
////		cout << "Zavrsni rad uspjesno dodat!" << endl;
////
////	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
////	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
////		1. zavrsni rad ima broj poglavlja veci od minimalnog
////		2. svako poglavlje ima broj karaktera veci od minimalnog
////		3. svako poglavlje je prihvaceno/odobreno
////	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
////	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
////*/
////
//////parametri: brojIndeksa, datumOdbrane
////	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
////	if (zr1 != nullptr)
////		cout << *zr1 << endl;
////
////	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
////	if (zr1 != nullptr)
////		cout << *zr1 << endl;
////
////	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
////	nastavnici[0]->Info();
////
////	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
////	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
////	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine."	.
////	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
////	//cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;
////
////	for (int i = 0; i < max; i++) {
////		delete nastavnici[i];
////		nastavnici[i] = nullptr;
////	}
//
//	system("pause");
//	return 0;
//}
//
//
//
//
//
//
//
//
//
//






















































































//#include<iostream>
//#include<string>
//#include<vector>
//#include<regex>
//#include<mutex>
//#include<thread>
//#include<fstream>
//using namespace std;
//
///****************************************************************************
//1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
//3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
//4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
//****************************************************************************/
//
//const char* nedozvoljena_operacija = "Nedozvoljena operacija";
//const char* not_set = "NOT_SET";
//mutex m;
//enum Sortiranje { ASC, DESC };
//enum Predmet { MATEMATIKA, FIZIKA, HEMIJA, GEOGRAFIJA, NOT_SET };
//enum Razred { I = 1, II, III, IV };
//
//char* AlocirajNizKaraktera(const char* sadrzaj) {
//	if (sadrzaj == nullptr)
//		return nullptr;
//	int vel = strlen(sadrzaj) + 1;
//	char* temp = new char[vel];
//	strcpy_s(temp, vel, sadrzaj);
//	return temp;
//}
//template <class T1, class T2, int max>
//class Kolekcija {
//	T1* _elementi1[max] = { nullptr };
//	T2* _elementi2[max] = { nullptr };
//	int _trenutnoElemenata;
//	bool _dozvoliDupliranje;
//	Sortiranje _sortiranje;
//public:
//	Kolekcija(Sortiranje sortiranje = ASC, bool dozvoliDupliranje = true) {
//		_trenutnoElemenata = 0;
//		_sortiranje = sortiranje;
//		_dozvoliDupliranje = dozvoliDupliranje;
//	}
//	~Kolekcija() {
//		for (size_t i = 0; i < _trenutnoElemenata; i++) {
//			delete _elementi1[i]; _elementi1[i] = nullptr;
//			delete _elementi2[i]; _elementi2[i] = nullptr;
//		}
//	}
//	Kolekcija(const Kolekcija& obj)
//	{
//		_trenutnoElemenata = obj._trenutnoElemenata;
//		_dozvoliDupliranje = obj._dozvoliDupliranje;
//		_sortiranje = obj._sortiranje;
//		for (size_t i = 0; i < obj.GetTrenutno(); i++)
//		{
//			_elementi1[i] = new T1(*obj._elementi1[i]);
//			_elementi2[i] = new T2(*obj._elementi2[i]);
//		}
//	}
//	Kolekcija& operator=(const Kolekcija& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_trenutnoElemenata = obj._trenutnoElemenata;
//		_dozvoliDupliranje = obj._dozvoliDupliranje;
//		_sortiranje = obj._sortiranje;
//		for (size_t i = 0; i < obj.GetTrenutno(); i++)
//		{
//			_elementi1[i] = new T1(*obj._elementi1[i]);
//			_elementi2[i] = new T2(*obj._elementi2[i]);
//		}
//			return *this;
//	}
//	int GetTrenutno() const { return _trenutnoElemenata; }
//	int GetMax() const { return max; }
//	void AddElement(const T1& element1, const T2& element2)
//	{
//		if (!_dozvoliDupliranje)
//		{
//			for (size_t i = 0; i < _trenutnoElemenata; i++)
//			{
//				if (*_elementi1[i]==element1 || *_elementi2[i]==element2)
//				{
//					throw exception("Elementi vec postoje \n");
//				}
//			}
//		}
//		if (_trenutnoElemenata < max-1)
//		{
//			_elementi1[_trenutnoElemenata] = new T1(element1);
//			_elementi2[_trenutnoElemenata] = new T2(element2);
//			_trenutnoElemenata++;
//			sortiraj();
//			return;
//		}
//		else {
//			throw exception("Kolekcija je puna \n");
//		}
//	}
//	void sortiraj() {
//		bool flag = true;
//		if (_sortiranje==0)
//		{
//			while (flag)
//			{
//				flag = false;
//				for (size_t i = 0; i < _trenutnoElemenata-1; i++)
//				{
//					if (*_elementi1[i]>*_elementi1[i+1])
//					{
//						swap(*_elementi1[i], *_elementi1[i + 1]);
//						swap(*_elementi2[i], *_elementi2[i + 1]);
//						flag = true;
//					}
//				}
//			}
//			return;
//		}
//		else {
//			while (flag)
//			{
//				flag = false;
//				for (size_t i = 0; i < _trenutnoElemenata - 1; i++)
//				{
//					if (*_elementi1[i] < * _elementi1[i + 1])
//					{
//						swap(_elementi1[i], _elementi1[i + 1]);
//						swap(_elementi2[i], _elementi2[i + 1]);
//						flag = true;
//					}
//				}
//			}
//		}
//	}
//	T1& GetElement1(int lokacija) const {
//		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
//			throw exception(nedozvoljena_operacija);
//		return *_elementi1[lokacija];
//	}
//	T2& GetElement2(int lokacija) const {
//		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
//			throw exception(nedozvoljena_operacija);
//		return *_elementi2[lokacija];
//	}
//	void SetElement2(int lokacija, T2 ele2) {
//		_elementi2[lokacija] = ele2;
//	}
//	friend ostream& operator<<(ostream & COUT, const Kolekcija & obj) {
//		for (size_t i = 0; i < obj.GetTrenutno(); i++)
//			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
//		return COUT;
//	}
//};
//
//class Aktivnost {
//	shared_ptr<Razred> _razred;
//	string _opis;
//	int _ocjena;//1-5
//public:
//	Aktivnost(Razred razred = I, int ocjena = 0, string opis = not_set) {
//		_ocjena = ocjena;
//		_opis = opis;
//		_razred = make_shared<Razred>(razred);
//	}
//	bool operator==(const Aktivnost &obj) {
//		return _razred == obj._razred && _opis == obj._opis && _ocjena == obj._ocjena;
//	}
//	int  GetOcjenu() const { return _ocjena; }
//	string GetOpis() const { return _opis; }
//	Razred GetRazred() const { return *_razred; }
//
//	friend ostream& operator<<(ostream& COUT, const Aktivnost& obj) {
//		COUT << *obj._razred << " " << obj._ocjena << " " << obj._opis << endl;
//		return COUT;
//	}
//};
//
//class Polaznik {
//protected:
//	char* _imePrezime;
//	string _brojTelefona;
//	bool isValidanBroj(string brojTelefona) {
//		regex pravilo("\\+\\d{3}\\s?\\(?\\d{2}\\)?\\s?\\d{3}\\-\\d{3}");
//		return regex_match(brojTelefona, pravilo);
//	}
//public:
//	Polaznik(string imePrezime, string brojTelefona) : _imePrezime(AlocirajNizKaraktera(imePrezime.c_str())) {
//		_brojTelefona = (isValidanBroj(brojTelefona))?  brojTelefona : not_set;
//	}
//	Polaznik(const Polaznik& obj)
//	{
//		_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
//		_brojTelefona = (isValidanBroj(obj._brojTelefona)) ? obj._brojTelefona : not_set;
//	}
//	Polaznik& operator=(const Polaznik& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
//		_brojTelefona = (isValidanBroj(obj._brojTelefona)) ? obj._brojTelefona : not_set;
//			return *this;
//	}
//	~Polaznik() { delete[] _imePrezime; }
//	char* GetImePrezime() { return _imePrezime; }
//	string GetTelefon() { return _brojTelefona; }
//	virtual void PredstaviSe() = 0;
//};
//
//class Ucenik:public Polaznik
//{
//	Kolekcija<Predmet, Aktivnost, 16>* _aktivnosti;
//public:
//	Ucenik(string ime,string brojTelefona):Polaznik(ime,brojTelefona)
//	{
//		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>;
//	}
//	Ucenik(const Ucenik& obj):Polaznik(obj)
//	{
//		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(*obj._aktivnosti);
//	}
//	Ucenik& operator=(const Ucenik& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		(Polaznik&)(*this) = (obj);
//		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(*obj._aktivnosti);
//
//		return *this;
//	}
//	~Ucenik() { delete _aktivnosti; _aktivnosti = nullptr; }
//	Kolekcija<Predmet, Aktivnost, 16>& GetAktivnosti() { return *_aktivnosti; };
//	friend ostream& operator<<(ostream& COUT, Ucenik& n)
//	{
//		COUT << "Ime: " << n.GetImePrezime() << endl;
//		COUT << "Broj telefona: " << n.GetTelefon() << endl;
//		COUT << "Aktivnosti: " << endl;
//		COUT << n.GetAktivnosti();
//		return COUT;
//	}
//	float prosjecnaOcjena() {
//		float prosjek = 0;
//
//		for (size_t i = 0; i < _aktivnosti->GetTrenutno(); i++)
//		{
//			prosjek += _aktivnosti->GetElement2(i).GetOcjenu();
//		}
//		return prosjek /= (float)_aktivnosti->GetTrenutno(); 
//		
//	}
//	void PredstaviSe() {};
//};
//class Skola {
//	char* _naziv;
//	vector<Ucenik> _ucenici;
//public:
//	Skola(const char* naziv = nullptr) {
//		_naziv = AlocirajNizKaraktera(naziv);
//	}
//	Skola(const Skola& obj)
//	{
//		_naziv = AlocirajNizKaraktera(obj._naziv);
//		for (size_t i = 0; i < obj._ucenici.size(); i++)
//		{
//			_ucenici.push_back(obj._ucenici[i]);
//		}
//	}
//	Skola& operator=(const Skola& obj)
//	{
//		if (&obj == this)
//		{
//			return *this;
//		}
//		_naziv = AlocirajNizKaraktera(obj._naziv);
//		for (size_t i = 0; i < obj._ucenici.size(); i++)
//		{
//			_ucenici.push_back(obj._ucenici[i]);
//		}
//		return *this;
//	}
//	~Skola() {
//		delete[] _naziv; _naziv = nullptr;
//	}
//	void operator()(string ime, string brojTelefona)
//	{
//		for (size_t i = 0; i < _ucenici.size(); i++)
//		{
//			if (_ucenici[i].GetImePrezime() == ime || _ucenici[i].GetTelefon() == brojTelefona)
//			{
//				throw exception("Ucenik vec postoji");
//				return;
//			}
//		}
//		Ucenik noviUcenik(ime, brojTelefona);
//		_ucenici.push_back(noviUcenik);
//	}
//	char* GetNaziv()const { return _naziv; }
//	vector<Ucenik>& GetUcenici() { return _ucenici; };
//	bool DodajAktivnost(string ime, const Predmet& predmet, const  Aktivnost& aktivnost)
//	{
//		for (vector<Ucenik>::iterator ucenik = _ucenici.begin(); ucenik != _ucenici.end(); ucenik++)
//		{
//			if (ucenik->GetImePrezime() == ime)
//			{
//				for (size_t j = 0; j < ucenik->GetAktivnosti().GetTrenutno(); j++)
//				{
//					if (ucenik->GetAktivnosti().GetElement2(j).GetRazred() == aktivnost.GetRazred())
//					{
//						if (ucenik->GetAktivnosti().GetTrenutno() >= 4)
//						{
//							//throw exception("Dostignut maximalan broj aktivnosti");
//							return false;
//						}
//						if (ucenik->GetAktivnosti().GetElement2(j) == aktivnost)
//						{
//							/*throw exception("Aktivnost vec postoji");*/
//							return false;
//						}
//						if (ucenik->GetAktivnosti().GetElement1(j) == predmet)
//						{
//							return false;
//						}
//					}
//				}
//				ucenik->GetAktivnosti().AddElement(predmet, aktivnost);
//				bool flag = false;
//				for (size_t j = 0; j < ucenik->GetAktivnosti().GetTrenutno(); j++) {
//					if (ucenik->GetAktivnosti().GetElement2(j).GetOcjenu() > 1 && strcmp(ucenik->GetTelefon().c_str(), not_set) != 0)
//						flag = true;
//				}
//				if (ucenik->GetAktivnosti().GetTrenutno()==4 && flag)
//				{
//					//Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X
//					thread sms([&] {
//						m.lock();
//						cout << "Uspjesno ste okoncali aktivnosti u okviru " << aktivnost.GetRazred() << " razreda sa prosjecnom ocjenom " << ucenik->prosjecnaOcjena() << endl;
//						m.unlock();
//						});
//					sms.join();
//				}
//				return true;
//			}
//		}
//	}
//
//	pair<Polaznik*, float> GetNajboljegUcenika() {
//		int index = -1;
//		for (size_t i = 0; i < _ucenici.size() - 1; i++)
//		{
//			if (_ucenici[i].GetAktivnosti().GetTrenutno() > 0 && _ucenici[i + 1].GetAktivnosti().GetTrenutno() > 0)
//			{
//				if (_ucenici[i].prosjecnaOcjena() > _ucenici[i + 1].prosjecnaOcjena())
//				{
//					index = i;
//				}
//				else
//				{
//					index = i + 1;
//				}
//			}
//		}
//		Polaznik* temp = new Ucenik(_ucenici[index].GetImePrezime(), _ucenici[index].GetTelefon());
//		float prosjecna = _ucenici[index].prosjecnaOcjena();
//		if (index >= 0)
//		{
//			return make_pair(temp, prosjecna);
//		}
//		else {
//			return make_pair(new Ucenik("---", "---"), 0);
//		}
//	}
//	bool SpasiUFajl(const char* nazivFajla, bool brisanje = false)
//	{
//		if (brisanje)
//		{
//			ofstream upis(nazivFajla, ios::app);
//			if (upis.fail())
//			{
//				return false;
//			}
//		    upis << *this << endl;
//			upis.close();
//			return true;
//		}
//		else {
//			ofstream upis(nazivFajla);
//			if (upis.fail())
//			{
//				return false;
//			}
//			upis << *this << endl;
//			upis.close();
//			return true;
//		}
//
//	}
//	friend ostream& operator<<(ostream& COUT, Skola& obj) {
//		COUT << "Skola: " << obj._naziv << endl;
//		COUT << "Ucenici: " << endl;
//		for (size_t i = 0; i < obj._ucenici.size(); i++)
//			COUT << obj._ucenici[i] << endl;
//		return COUT;
//	}
//};
//
//int main() {
//	Kolekcija<int, int, 10> kolekcija1(DESC, false);
//	try {
//		kolekcija1.AddElement(1, 2);
//		//dupliranje elemenata nije dozvoljeno
//		kolekcija1.AddElement(1, 2);
//	}
//	catch (exception & ex) {
//		cout << ex.what();
//	}
//
//	/*nakon svakog dodavanja, elemente sortirati prema T1 i vrijednosti atributa _sortiranje*/
//	for (size_t i = 1; i < kolekcija1.GetMax() - 1; i++)
//		kolekcija1.AddElement(rand(), rand());
//
//	cout << kolekcija1 << endl;
//
//	try {
//		//prekoracen maksimalan broj elemenata
//		kolekcija1.AddElement(rand(), rand());
//	}
//	catch (exception & ex) {
//		cout << ex.what();
//	}
//	cout << kolekcija1 << endl;
//
//	Kolekcija<int, int, 10> kolekcija2(kolekcija1);
//	cout << kolekcija2 << endl;
//
//	Skola gimnazijaMostar("GIMNAZIJA MOSTAR");
//	//dodaje novog ucenika u skolu
//	gimnazijaMostar("Jasmin Azemovic", "+387(61)111-222");
//	gimnazijaMostar("Adel Handzic", "+387(61)333-444");
//
//	/*
//	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
//	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
//	*/
//	gimnazijaMostar("Telefon NotValidFormat", "387 61)333-444");
//
//	try
//	{
//		/*onemoguciti dodavanje ucenika sa istim imenom i prezimenom ili brojem telefona*/
//		gimnazijaMostar("Adel Handzic", "+387(61)333-444");
//	}
//	catch (exception & ex)
//	{
//		cout << ex.what() << endl;
//	}
//
//	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematike koje se odrzava u Konjicu 07.02.2019")))
//		cout << "Aktivnost uspjesno dodana" << endl;
//	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/
//	if (!gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Aktivnosti iz matematike")))
//		cout << "Aktivnost nije uspjesno dodana" << endl;
//	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", HEMIJA, Aktivnost(I, 5, "Priprema otopina za vjezbe iz predmeta Hemija")))
//		cout << "Aktivnost uspjesno dodana" << endl;
//	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", FIZIKA, Aktivnost(I, 4, "Analiza stepena apsorpcije materijala ")))
//		cout << "Aktivnost uspjesno dodana" << endl;
//
//	/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
//	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/
//	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", GEOGRAFIJA, Aktivnost(I, 4, "Izrada 5 reljefa Mostara")))
//		cout << "Aktivnost uspjesno dodana" << endl;
//	if (gimnazijaMostar.DodajAktivnost("Adel Handzic", MATEMATIKA, Aktivnost(I, 5, "Izrada skripte na temu integralni racun")))
//		cout << "Aktivnost uspjesno dodana" << endl;
//
//	//ispisuje sve ucenike i njihove aktivnosti
//	cout << gimnazijaMostar << endl;
//
//
//	pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
//	cout << "Najbolji ucenik je " << par.first->GetImePrezime() << " sa prosjekom " << par.second << endl;
//
//	/*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
//	Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/
//
//	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt"))
//		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
//	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt", true))
//		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
//
//	//cin.get();
//	system("PAUSE");
//	return 0;
//}
//
//
//
//
//
//






























//#include <iostream>
//#include <vector>
//#include <string>
//#include <regex>
//#include <thread>
//#include <mutex>
//#include <chrono>
//using namespace std;
//
//mutex m;
//const char* crt = "\n---------------------------------------\n";
//
//class DatumVrijeme {
//	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
//public:
//	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
//		_dan = new int(dan);
//		_mjesec = new int(mjesec);
//		_godina = new int(godina);
//		_sati = new int(sati);
//		_minuti = new int(minuti);
//
//	}
//	DatumVrijeme(const DatumVrijeme& obj)
//	{
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		_sati = new int(*obj._sati);
//		_minuti = new int(*obj._minuti);
//	}
//	DatumVrijeme& operator=(const DatumVrijeme& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		_sati = new int(*obj._sati);
//		_minuti = new int(*obj._minuti);
//			return *this;
//	}
//	bool operator==(DatumVrijeme datum) {
//		return *_dan == *datum._dan && *_mjesec == *datum._mjesec && *_godina == *datum._godina && *_sati == *datum._sati;
//	}
//	~DatumVrijeme() {
//		delete _dan; _dan = nullptr;
//		delete _mjesec; _mjesec = nullptr;
//		delete _godina; _godina = nullptr;
//		delete _sati; _sati = nullptr;
//		delete _minuti; _minuti = nullptr;
//
//	}
//	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
//		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
//		return COUT;
//	}
//};
//
//template<class T1, class T2 = int>
//class FITKolekcija {
//	T1* _elementi1;
//	T2* _elementi2;
//	int _trenutno;
//public:
//	FITKolekcija() {
//		_elementi1 = nullptr;
//		_elementi2 = nullptr;
//		_trenutno = 0;
//	}
//	~FITKolekcija() {
//		delete[] _elementi1; _elementi1 = nullptr;
//		delete[] _elementi2; _elementi2 = nullptr;
//	}
//	FITKolekcija(const FITKolekcija& obj)
//	{
//		_trenutno = obj._trenutno;
//		_elementi1 = new T1[_trenutno];
//		_elementi2 = new T2[_trenutno];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//	}
//	T1* GetT1() { return _elementi1; }
//	T2* GetT2() { return _elementi2; }
//	int GetTrenutno() { return _trenutno; }
//	void Dodaj(const T1& element1, const T2& element2)
//	{
//		//dio koda zaduzen ukoliko je dupliciranje elemenata zabranjeno
//		/*for (size_t i = 0; i <_trenutno ; i++)
//		{
//			if (_elementi1[i]==element1 && _elementi2[i]==element2)
//			{
//				cout << "Elementi vec postoje" << endl;
//				return ;
//			}
//		}*/
//		T1* temp1 = new T1[_trenutno + 1];
//		T2* temp2 = new T2[_trenutno + 1];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			temp1[i] = _elementi1[i];
//			temp2[i] = _elementi2[i];
//		}
//		delete[]_elementi1;
//		delete[]_elementi2;
//		_elementi1 = temp1;
//		_elementi2 = temp2;
//		_elementi1[_trenutno] = element1;
//		_elementi2[_trenutno] = element2;
//		_trenutno++;
//	}
//	void Ukloni(int index) {
//		if (index>=0 && index<_trenutno)
//		{
//			T1* temp1 = new T1[_trenutno - 1];
//			T2* temp2 = new T2[_trenutno - 1];
//			int j = 0;
//			for (size_t i = 0; i < _trenutno; i++)
//			{
//				if (i==index)
//				{
//					j++;
//				}
//				temp1[i] = _elementi1[j];
//				temp2[i] = _elementi2[j];
//				j++;
//			}
//			delete[]_elementi1;
//			delete[]_elementi2;
//			_elementi1 = temp1;
//			_elementi2 = temp2;
//			_trenutno--;
//		}
//	}
//	void Sortiraj()
//	{
//		bool flag = true;
//		while (flag)
//		{
//			flag = false;
//			for (size_t i = 0; i < _trenutno-1; i++)
//			{
//				if (_elementi1[i]>_elementi1[i+1])
//				{
//					swap(_elementi1[i], _elementi1[i + 1]);
//					swap(_elementi2[i], _elementi2[i + 1]);
//					flag = true;
//				}
//			}
//		}
//	}
//	void DodajNaLokaciju(const T1& element1, const T2& element2, int index)
//	{
//		if (index>=0 && index<_trenutno)
//		{
//			_elementi1[index] = element1;
//			_elementi2[index] = element2;
//			return;
//		}
//		else
//		{
//			cout << "Nepostojeca lokacija" << endl;
//		}
//	}
//	FITKolekcija<T1, T2>* GetJedinstveni() {
//		FITKolekcija<T1, T2>* temp = new FITKolekcija<T1, T2>[_trenutno];
//		bool flag = false;
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			for (size_t j = 0; j < _trenutno; j++)
//			{
//				if (i!=j)
//				{
//					if (_elementi1[i] == _elementi1[j] && _elementi2[i]==_elementi2[j])
//					{
//						flag = true;
//					}
//				}
//			}
//			if (!flag)
//			{
//				temp->Dodaj(_elementi1[i], _elementi2[i]);
//			}
//		}
//		return temp; 
//	}
//	friend ostream& operator<< (ostream& COUT, FITKolekcija& obj) {
//		for (size_t i = 0; i < obj._trenutno; i++)
//			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
//		return COUT;
//	}
//};
//
//enum vrstaDokumenta { PDF, DOC, TXT, HTML };
//
//class Dokument {
//	vrstaDokumenta _vrsta;
//	string _naziv;
//	string _sadrzaj;
//	int _brojStranica;
//public:
//	Dokument() { _brojStranica = 0; }
//	Dokument(vrstaDokumenta vrsta, string naziv) {
//		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
//	}
//	string GetNaziv() { return _naziv; };
//	string GetSadrzaj()const { return _sadrzaj; };
//	vrstaDokumenta GetVrsta() { return _vrsta; };
//	void UvecajBrojStranica() { _brojStranica++; }
//	int GetBrojStranica() { return _brojStranica; }
//	bool nazivValidan()
//	{
//		regex pravilo("\\w{5,15}\\.(doc|txt|pdf)");
//		return regex_match(_naziv, pravilo);
//	}
//	bool sadrziZabranjeneRijeci(string rijec)
//	{
//		regex pravilo(rijec);
//		return regex_search(_sadrzaj, pravilo);
//	}
//	void DodajSadrzaj(string noviSadrzaj)
//	{
//		int temp = strlen(_sadrzaj.c_str())/30;
//		_sadrzaj += noviSadrzaj;
//		if (strlen(_sadrzaj.c_str()) / 30 > temp)
//		{
//			this->UvecajBrojStranica();
//		}
//	}
//	
//	friend ostream& operator<<(ostream& COUT, Dokument& obj) {
//		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
//		return COUT;
//	}
//};
//class Uredjaj {
//protected:
//	char* _proizvodjac;
//	char* _model;
//public:
//	Uredjaj(const char* proizvodjac,const char* model) {
//		int vel = strlen(proizvodjac) + 1;
//		_proizvodjac = new char[vel];
//		strcpy_s(_proizvodjac, vel, proizvodjac);
//		vel = strlen(model) + 1;
//		_model = new char[vel];
//		strcpy_s(_model, vel, model);
//	}
//	Uredjaj(const Uredjaj& obj)
//	{
//		int vel = strlen(obj._proizvodjac) + 1;
//		_proizvodjac = new char[vel];
//		strcpy_s(_proizvodjac, vel, obj._proizvodjac);
//		vel = strlen(obj._model) + 1;
//		_model = new char[vel];
//		strcpy_s(_model, vel, obj._model);
//	}
//	~Uredjaj() {
//		delete[] _proizvodjac; _proizvodjac = nullptr;
//		delete[] _model; _model = nullptr;
//	}
//	friend ostream& operator<<(ostream& COUT, Uredjaj& obj) {
//		COUT << obj._proizvodjac << "." << obj._model << endl;
//		return COUT;
//	}
//};
//class Printer:public Uredjaj {
//	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
//	vector<string> _zabranjeneRijeci;
//public:
//	Printer(const char* proizvodjac, const char* model) :Uredjaj(proizvodjac, model)
//	{};
//	Printer(Printer& obj):Uredjaj(obj)
//	{
//		_printaniDokumenti = obj._printaniDokumenti;
//		for (size_t i = 0; i < obj.GetZabranjeneRijeci().size(); i++)
//		{
//			_zabranjeneRijeci.push_back(obj.GetZabranjeneRijeci()[i]);
//		}
//	}
//	FITKolekcija<DatumVrijeme, Dokument>& GetPrintaniDokumenti() { return _printaniDokumenti; };
//	void DodajZabranjenuRijec(string zabranjenaRijec)
//	{
//		for (vector<string>::iterator i = _zabranjeneRijeci.begin(); i != _zabranjeneRijeci.end(); i++)
//		{
//			if (*i==zabranjenaRijec)
//			{
//				cout << "Rijec vec zabranjena" << endl;
//				return;
//			}
//		}
//		_zabranjeneRijeci.push_back(zabranjenaRijec);
//	}
//	vector<string>&  GetZabranjeneRijeci() { return _zabranjeneRijeci; };
//	void Printaj(const DatumVrijeme datumVrijeme,  Dokument dokument)
//	{
//		if (dokument.nazivValidan())
//		{
//			for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
//			{
//				if (dokument.sadrziZabranjeneRijeci(_zabranjeneRijeci[i]))
//				{
//					_printaniDokumenti.Dodaj(datumVrijeme, dokument);
//					throw exception("Sadrzi zabranjene rijeci \n");
//					return;
//				}
//			}
//			_printaniDokumenti.Dodaj(datumVrijeme, dokument);
//			thread print([dokument](){
//				m.lock();
//				this_thread::sleep_for(chrono::seconds(1));
//				cout << crt << endl;
//				cout << "::::PRINT::::" << endl;
//				this_thread::sleep_for(chrono::seconds(1));
//				cout << dokument.GetSadrzaj() << endl;
//				this_thread::sleep_for(chrono::seconds(1));
//				cout << "::::KRAJ PRINTA::::" << endl;
//				this_thread::sleep_for(chrono::seconds(1));
//				cout << crt << endl;
//				m.unlock();
//				});
//			print.join();
//			
//			return;
//		}
//		else
//		{
//			throw exception("Naziv nije validan \n");
//			_printaniDokumenti.Dodaj(datumVrijeme, dokument);
//		}
//
//	}
//	float GetProsjecanBrojStranicaPoDatumu(DatumVrijeme datum)
//	{
//		int brojac=0;
//		float temp = 0;
//		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
//		{
//			if (_printaniDokumenti.GetT1()[i]==datum)
//			{
//				temp += _printaniDokumenti.GetT2()[i].GetBrojStranica();
//				brojac++;
//			}
//		}
//		return float(temp / (brojac));
//	}
//
//		//nedovrseno
//	//string GetTopZabranjenuRijec() {
//	//}
//
//	/*void UkloniDokumente()
//	{
//		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
//		{
//			if (_printaniDokumenti.GetT2()[i].nazivValidan())
//			{
//				for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
//				{
//					if (_printaniDokumenti.GetT2()[i].sadrziZabranjeneRijeci(_zabranjeneRijeci[i]))
//					{
//						_printaniDokumenti.Ukloni(i);
//					}
//				}
//			}
//			else {
//				_printaniDokumenti.Ukloni(i);
//			}
//		}
//
//	}*/
//};
//
//void main()
//{
//	/****************************************************************************
//	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
//	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
//	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
//	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
//	****************************************************************************/
//
//#pragma region TestiranjeDatumVrijeme
//	DatumVrijeme danas(1, 2, 2017, 10, 15);
//	DatumVrijeme sutra(danas);
//	DatumVrijeme prekosutra;
//	prekosutra = danas;
//	cout << danas << endl << sutra << endl << prekosutra << crt;
//
//#pragma endregion
//#pragma region FITKolekcija
//	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;
//
//	FITKolekcija<int, int> brojevi;
//	brojevi.Dodaj(v196, v6);
//	brojevi.Dodaj(v13, v32);
//	brojevi.Dodaj(v98, v196);
//	brojevi.Dodaj(v63, v13);
//	brojevi.Dodaj(v98, v196);
//	brojevi.Dodaj(v196, v6);
//
//	cout << brojevi << crt;
//	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
//	brojevi.Sortiraj();
//	cout << brojevi << crt;
//	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
//	brojevi.DodajNaLokaciju(v109, v6, 2);
//	cout << brojevi << crt;
//	brojevi.Sortiraj();
//	cout << brojevi << crt;
//	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE 
//	(POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
//	FITKolekcija<int, int>* jedinstveni = brojevi.GetJedinstveni();
//	cout << *jedinstveni << crt;
//	*jedinstveni = brojevi;
//	cout << *jedinstveni << crt;
//
//	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
//	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. 
//	//ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
//	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO RE");
//	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
//
//	Dokument ispitBaze(DOC, "ispitBaze.doc");
//	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT");
//	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU
//
//	Printer hp3200("HP", "3200");
//	//PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
//	hp3200.DodajZabranjenuRijec("RE");// :)
//	hp3200.DodajZabranjenuRijec("RAT");
//	hp3200.DodajZabranjenuRijec("UBITI");
//	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
//	hp3200.DodajZabranjenuRijec("MRZITI");
//	try
//	{
//		/*
//		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
//		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
//		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
//		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
//		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
//		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
//		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
//		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
//		SADRŽAJ DOKUMENTA KOJI SE PRINTA
//		*/
//
//		//linija ispod zakomentarisana radi nastavka testiranja(kod funkcionise pravilno i pritom prekida izvrsavanje jer u dokumentu ispitPRIII postoji zabranjena rijec)
//		//hp3200.Printaj(danas, ispitPRIII);
//
//		hp3200.Printaj(danas, ispitBaze);
//
//		/*
//		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
//		VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
//		*/
//
//	}
//	catch (exception & err)
//	{
//		cout << err.what() << endl;
//	}
//
//	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
//	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
//	
//	//nedovrseno
//	//cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;
//
//	Printer hp4000(hp3200);
//	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
//
//	//nedovrseno
//	//cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
//	//hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
//	//cout << hp4000 << crt;
//
//#pragma endregion
//	system("PAUSE");
//}
//


























































































//#include<iostream>
//#include<string>
//#include<vector>
//#include<string>    
//#include<sstream>
//#include<exception>
//#include<regex>
//
//using namespace std;
//const char* crt = "\n---------------------------------------\n";
//
//enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
//enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
//const char* ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
//const char* ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };
//
//template<class T1, class T2>
//class Kolekcija {
//	T1* _elementi1;
//	T2* _elementi2;
//	int _trenutno;
//public:
//	Kolekcija()
//	{
//		_elementi1 = nullptr;
//		_elementi2 = nullptr;
//		_trenutno = 0;
//	}
//	~Kolekcija()
//	{
//		delete[]_elementi1;
//		delete[]_elementi2;
//	}
//	Kolekcija(const Kolekcija& obj)
//	{
//		_trenutno = obj._trenutno;
//		_elementi1 = new T1[_trenutno];
//		_elementi2 = new T2[_trenutno];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//	}
//	Kolekcija& operator=(const Kolekcija& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_trenutno = obj._trenutno;
//		_elementi1 = new T1[_trenutno];
//		_elementi2 = new T2[_trenutno];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//		return *this;
//	}
//	void addElement(const T1& element1, const T2& element2)
//	{
//		T1* temp1 = new T1[_trenutno + 1];
//		T2* temp2 = new T2[_trenutno + 1];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			temp1[i] = _elementi1[i];
//			temp2[i] = _elementi2[i];
//		}
//		delete[]_elementi1;
//		delete[]_elementi2;
//		_elementi1 = temp1;
//		_elementi2 = temp2;
//		_elementi1[_trenutno] = element1;
//		_elementi2[_trenutno] = element2;
//		_trenutno++;
//	}
//	friend ostream& operator<<(ostream& cout,const  Kolekcija& obj)
//	{
//		for (size_t i = 0; i < obj.getTrenutno(); i++)
//		{
//			cout << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
//		}
//		return cout;
//	}
//	int getTrenutno()const {
//		return _trenutno;
//	}
//	T1 getElement1(int i)const { return _elementi1[i]; }
//	T2 getElement2(int i)const { return _elementi2[i]; }
//	void removeElement(int index)
//	{
//		if (index<0 || index>=_trenutno)
//		{
//			return;
//		}
//		int j = 0;
//		T1* temp1 = new T1[_trenutno -1];
//		T2* temp2 = new T2[_trenutno -1];
//		for (size_t i = 0; i < _trenutno; i++)
//		{
//			if (j==index)
//			{
//				j++;
//			}
//			temp1[i] = _elementi1[j];
//			temp2[i] = _elementi2[j];
//			j++;
//		}
//		delete[]_elementi1;
//		delete[]_elementi2;
//		_elementi1 = temp1;
//		_elementi2 = temp2;
//		_trenutno--;
//	}
//};
//class Datum {
//	int* _dan, * _mjesec, * _godina;
//public:
//	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
//		_dan = new int(dan);
//		_mjesec = new int(mjesec);
//		_godina = new int(godina);
//	}
//
//	Datum(const Datum& obj) {
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//	}
//	Datum& operator=(const Datum& obj) {
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//			return *this;
//	}
//
//	~Datum() {
//		delete _dan; _dan = nullptr;
//		delete _mjesec; _mjesec = nullptr;
//		delete _godina; _godina = nullptr;
//	}
//
//
//	friend ostream& operator<< (ostream& COUT, const Datum& obj) {
//		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
//		return COUT;
//	}
//};
//bool ProvjeriValidnostBrojaTelefona(string telefon) {//globalna funkcija
//	/*
//	broj telefona treba biti u formatu: +387(61)-222-333
//	*/
//	regex pravilo("\\+\\d{3}\\(\\d{2}\\)\\-\\d{3}\\-\\d{3}");
//	return regex_match(telefon, pravilo);
//}
//class Osoba {
//protected:
//	char* _imePrezime;
//	Datum* _datumRodjenja;
//	string _brojTelefona;
//public:
//	Osoba(const char* imePrezime, Datum datum) {
//		_imePrezime = new char[strlen(imePrezime) + 1];
//		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
//		_datumRodjenja = new Datum(datum);
//		_brojTelefona = "---";
//
//	}
//	Osoba(const Osoba& obj) :_brojTelefona(obj._brojTelefona) {
//		_imePrezime = new char[strlen(obj._imePrezime) + 1];
//		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
//		_datumRodjenja = new Datum(*obj._datumRodjenja);
//	}
//	Osoba& operator=(const Osoba& obj) {
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_brojTelefona = obj._brojTelefona;
//		_imePrezime = new char[strlen(obj._imePrezime) + 1];
//		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
//		_datumRodjenja = new Datum(*obj._datumRodjenja);
//		return *this;
//	}
//	~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
//	const char* getImePrezime() {
//		return _imePrezime;
//	}
//	bool setBrojTelefona(string brojTelefona) {
//		if (ProvjeriValidnostBrojaTelefona(brojTelefona)) {
//			_brojTelefona = brojTelefona;
//			return true;
//		}
//		return false;
//	}
//	friend ostream& operator<<(ostream& cout, const Osoba& obj)
//	{
//		cout << "Ime i prezime: " << obj._imePrezime << endl;
//		cout << "Datum rodjenja: " << *obj._datumRodjenja << endl;
//		cout << "Broj telefona: " << obj._brojTelefona << endl;
//		return cout;
//	}
//};
//class Nastavnik :public Osoba {
//	Kolekcija<Predmeti, Razredi>* _predmetiRazredi;
//public:
//	Nastavnik(const char* ime, Datum datumRodjenja) :Osoba(ime, datumRodjenja)
//	{
//		_predmetiRazredi = nullptr;
//	}
//	~Nastavnik()
//	{
//			delete _predmetiRazredi;
//			_predmetiRazredi = nullptr;
//	}
//	Nastavnik(const Nastavnik& obj):Osoba(obj)
//	{
//		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*obj._predmetiRazredi);
//	}
//	Nastavnik& operator=(const Nastavnik& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		(Osoba&)(*this) = obj;
//		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*obj._predmetiRazredi);
//		return *this;
//	}
//
//	Kolekcija<Predmeti, Razredi>& getPredmetiRazredi()const {
//		return *_predmetiRazredi;
//	}
//
//	bool AddPredmetRazred(const Predmeti& predmet,const Razredi& razred)
//	{
//		if (_predmetiRazredi==nullptr)
//		{
//			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
//		}
//		
//		for (size_t i = 0; i < _predmetiRazredi->getTrenutno(); i++)
//		{
//			if (_predmetiRazredi->getElement1(i)==predmet)
//			{
//				if (_predmetiRazredi->getElement2(i)==razred)
//				{
//					cout << "Nije moguce dodati isti predmet u istom razredu" << endl;
//					return false;
//				}
//			}
//		}
//		_predmetiRazredi->addElement(predmet, razred);
//		return true;
//	}
//	bool RemovePredmetRazred(const Predmeti& predmet) {
//		for (size_t i = 0; i < _predmetiRazredi->getTrenutno(); i++)
//		{
//			if (_predmetiRazredi->getElement1(i)==predmet)
//			{
//				_predmetiRazredi->removeElement(i);
//				cout << "Predmet uspjesno uklonjen" << endl;
//				return true;
//			}
//		}
//		cout << "Predmet nije pronadjen" << endl;
//		return false;
//	}
//	bool operator==(const Nastavnik& obj)
//	{
//		return strcmp(_imePrezime, obj._imePrezime) == 0 && _brojTelefona == obj._brojTelefona;
//	}
//	friend ostream& operator<<(ostream& cout, const Nastavnik& obj)
//	{
//		//cout << Osoba::_brojTelefona << endl;
//		cout << *obj._predmetiRazredi << endl;
//	}
//};
//class Ucenik : public Osoba {
//	int _brojUDnevniku;
//	Razredi _razred;
//	vector<Nastavnik*> _nastavnici;
//	Kolekcija<Predmeti, int> _predmetiOcjene;
//public:
//	Ucenik(const char* imePrezime,Datum datum,int brojDnevnik,Razredi razred):Osoba(imePrezime,datum)
//	{
//		_brojUDnevniku = brojDnevnik;
//		_razred = razred;
//	}
//	bool AddNastavnik(const Nastavnik& nastavnik)
//	{
//		for (size_t i = 0; i < _nastavnici.size(); i++)
//		{
//			if (*_nastavnici[i]==nastavnik)
//			{
//				cout << "Nastavnik vec dodan" << endl;
//				return false;
//			}
//		}
//		for (size_t i = 0; i < nastavnik.getPredmetiRazredi().getTrenutno(); i++)
//		{
//			if (nastavnik.getPredmetiRazredi().getElement2(i) == _razred)
//			{
//				_nastavnici.push_back(new Nastavnik(nastavnik));
//				cout << "Nastavnik uspjesno dodan" << endl;
//				return true;
//			}
//		}
//		cout << "Nastavnik ne predaje nista u razredu ucenika" << endl;
//		return false;
//	}
//	bool AddPredmetOcjenu(const Predmeti& predmet, int ocjena)
//	{
//		bool flag = false;
//		for (size_t i = 0; i < _nastavnici.size(); i++)
//		{
//			if (_nastavnici[i]->getPredmetiRazredi().getElement1(i)==predmet)
//			{
//				flag = true;
//			}
//		}
//		if (flag)
//		{
//			_predmetiOcjene.addElement(predmet, ocjena);
//			cout << "Ocjena uspjesnoo dodana" << endl;
//			return true;
//		}
//		else
//		{
//			cout << "Ucenik nema profesora koji predaje taj predmet" << endl;
//			return false;
//		}
//	}
//	vector<Nastavnik*>& getNastavnici() {
//		return _nastavnici;
//	}
//	Kolekcija<Predmeti, int>& getPredmetiOcjene() { return _predmetiOcjene; }
//	float GetProsjekByNastavnik(const char* imeNastavnika) {
//		float prosjek = 0;
//		for (size_t i = 0; i < _nastavnici.size(); i++)
//		{
//			if (strcmp(_nastavnici[i]->getImePrezime(), imeNastavnika) == 0)
//			{
//				for (size_t j = 0; j < _predmetiOcjene.getTrenutno(); j++)
//				{
//					prosjek += _predmetiOcjene.getElement2(j);
//				}
//				return prosjek / float(_predmetiOcjene.getTrenutno());
//			}	
//		}
//		cout << "Nastavnik ne postoji" << endl;
//		return 0;
//	}
//	friend ostream& operator<<(ostream& cout, const Ucenik& obj)
//	{
//		cout << static_cast<Osoba>(obj) << endl;
//		cout << "Broj u dnevniku: " << obj._brojUDnevniku << endl;
//		cout << "Razred: " << ispisRazredi[obj._razred]<< endl;
//		cout << "Predmeti i ocjene: " << endl;
//		for (size_t i = 0; i < obj._predmetiOcjene.getTrenutno(); i++)
//		{
//			cout << ispisPredmeti[obj._predmetiOcjene.getElement1(i)] << "  " << obj._predmetiOcjene.getElement2(i) << endl;
//		}
//		return cout;
//	}
//
//};
//
//
//void main() {
//
//	/****************************************************************************
//	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
//	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
//	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
//	5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
//	6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
//	****************************************************************************/
//
//#pragma region TestiranjeDatuma
//	Datum danas(26, 11, 2015);
//	Datum sutra(danas);
//	Datum prekosutra;
//	prekosutra = danas;
//	cout << danas << endl << sutra << endl << prekosutra << crt;
//#pragma endregion
//#pragma region testiranjekolekcije
//	Kolekcija<int, int> kolekcija1;
//	int brojelemenata = 15;
//	for (size_t i = 0; i < brojelemenata; i++)
//		kolekcija1.addElement(i, i);
//	cout << kolekcija1 << endl;
//	kolekcija1.removeElement(0);//uklanja element na osnovu lokacije
//	cout << kolekcija1.getElement1(0) << " " << kolekcija1.getElement2(0) << endl;
//	cout << kolekcija1 << endl;
//	Kolekcija<int, int> kolekcija2;
//	kolekcija2 = kolekcija1;
//	cout << kolekcija2 << crt;
//	if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
//		cout << "isti broj elemenata" << endl;
//	Kolekcija<int, int> kolekcija3(kolekcija2);
//	cout << kolekcija3 << crt;
//#pragma endregion
//#pragma region TestiranjeNastavnika
//	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
//	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
//	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
//	if (jasmin.AddPredmetRazred(Matematika, I1))
//		cout << "Predmet mat dodan" << endl;
//	
//	if (jasmin.AddPredmetRazred(Historija, I1))
//		cout << "Predmet hist dodan" << endl;
//
//	if (jasmin.AddPredmetRazred(Geografia, I1))
//		cout << "Predmet geo dodan" << endl;
//
//	if (jasmin.AddPredmetRazred(Geografia, I2))
//		cout << "Predmet geo2 dodan" << endl;
//
//	if (adel.AddPredmetRazred(Historija, III1))
//		cout << "Predmet hist dodan" << endl;
//
//	//zakomentirano radi potrebe testiranja u regionu testiranjeUcenika,kod radi normalno
//	/*if (adel.RemovePredmetRazred(Historija))
//		cout << "Predmet uklonjen!" << endl;*/
//
//	Nastavnik goran(adel);
//	if (goran == adel)
//		cout << "Nastavnici identicni" << endl;
//	goran = jasmin;
//	if (goran == jasmin)
//		cout << "Nastavnici identicni" << endl;
//
//	Kolekcija<Predmeti, Razredi> & predmetiRazredi = jasmin.getPredmetiRazredi();
//
//	if (!jasmin.setBrojTelefona("+38761111222"))
//		cout << "Broj telefona nije dodan!" << endl;
//	if (!jasmin.setBrojTelefona("+387-61-111-222"))
//		cout << "Broj telefona nije dodan!" << endl;
//	if (jasmin.setBrojTelefona("+387(61)-111-222"))
//		cout << "Broj telefona uspjesno dodan!" << endl;
//	//cout << jasmin << endl;
//#pragma endregion
//
//#pragma region TestiranjeUcenika
//	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
//	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
//	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
//
//	cout << crt << endl;
//
//	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
//	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
//	if (denis.AddNastavnik(jasmin))
//		cout << "Nastavnik uspjesno dodan" << endl;
//	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
//	if (denis.AddNastavnik(adel))
//		cout << "Nastavnik uspjesno dodan" << endl;
//
//	cout << crt << endl;
//
//	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
//	if (denis.AddPredmetOcjenu(Matematika, 3))
//		cout << "Ocjena uspjesno dodana" << endl;
//	if (denis.AddPredmetOcjenu(Historija, 4))
//		cout << "Ocjena uspjesno dodana" << endl;
//	//test prosjecne ocjene
//	/*if (denis.AddPredmetOcjenu(Historija, 3))
//		cout << "Ocjena uspjesno dodana" << endl;*/
//
//	cout << crt << endl;
//
//	vector<Nastavnik*> & nastavnici = denis.getNastavnici();
//	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;
//
//	cout << crt << endl;
//	
//
//	Kolekcija<Predmeti, int> & uspjeh = denis.getPredmetiOcjene();
//	cout << "Denis ima " << uspjeh.getTrenutno() << " polozenih predmeta" << endl;
//	cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;
//	cout << "Prosjecna ocjena kod nastavnika Adel Handzic je " << denis.GetProsjekByNastavnik("Adel Handzic") << endl;
//
//	cout << crt << endl;
//	cout << crt << endl;
//
//	Ucenik denis2(denis);
//	cout << denis << endl;
//	cout << denis2 << endl;
//
//#pragma endregion
//	system("pause");
//}
//















































































//#include <iostream>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <thread>
//#include <mutex>
//using namespace std;
//
//mutex m;
//#pragma warning(disable:4996)
//const char* crt = "\n-------------------------------------------\n";
//enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
//
//const float minimalan_prosjek = 4.5;
//
//char* AlocirajNizKaraktera(const char* sadrzaj) {
//	if (sadrzaj == nullptr)
//		return nullptr;
//	int vel = strlen(sadrzaj) + 1;
//	char* temp = new char[vel];
//	strcpy_s(temp, vel, sadrzaj);
//	return temp;
//}
//
//template<class T1, class T2>
//class Kolekcija {
//	T1* _elementi1;
//	T2* _elementi2;
//	int* _trenutno;
//public:
//	Kolekcija() {
//		_elementi1 = nullptr;
//		_elementi2 = nullptr;
//		_trenutno = new int(0);
//	}
//	Kolekcija(const Kolekcija& obj)
//	{
//		_trenutno = new int(*obj._trenutno);
//		_elementi1 = new T1[*_trenutno];
//		_elementi2 = new T2[*_trenutno];
//		for (size_t i = 0; i < *_trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//	}
//	Kolekcija& operator=(const Kolekcija& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_trenutno = new int(*obj._trenutno);
//		_elementi1 = new T1[*_trenutno];
//		_elementi2 = new T2[*_trenutno];
//		for (size_t i = 0; i < *_trenutno; i++)
//		{
//			_elementi1[i] = obj._elementi1[i];
//			_elementi2[i] = obj._elementi2[i];
//		}
//			return *this;
//	}
//	~Kolekcija() {
//		delete[]_elementi1; _elementi1 = nullptr;
//		delete[]_elementi2; _elementi2 = nullptr;
//		delete _trenutno; _trenutno = nullptr;
//	}
//
//	void AddElement(const T1& element1, const T2& element2)
//	{
//		T1* temp1 = new T1[*_trenutno + 1];
//		T2* temp2 = new T2[*_trenutno + 1];
//		for (size_t i = 0; i < *_trenutno; i++)
//		{
//			temp1[i] = _elementi1[i];
//			temp2[i] = _elementi2[i];
//		}
//		delete[] _elementi1; delete[] _elementi2;
//		temp1[*_trenutno] = element1;
//		temp2[*_trenutno] = element2;
//		_elementi1 = temp1; _elementi2 = temp2;
//		temp1 = nullptr; temp2 = nullptr;
//		(*_trenutno)++;
//	}
//
//	void SortOpadajuciByT2() {
//		bool flag = true;
//		while (flag)
//		{
//			flag = false;
//			for (size_t i = 0; i < (*_trenutno)-1 ; i++)
//			{
//				if (_elementi2[i] < _elementi2[i + 1])
//				{
//					swap(_elementi2[i], _elementi2[i + 1]);
//					swap(_elementi1[i], _elementi1[i + 1]);
//					flag = true;
//				}
//			}
//		}
//	}
//
//	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
//	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
//	int getTrenutno() { return *_trenutno; }
//	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
//		for (size_t i = 0; i < *obj._trenutno; i++)
//			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
//		return COUT;
//	}
//};
//
//class DatumVrijeme {
//	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
//public:
//	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
//		_dan = new int(dan);
//		_mjesec = new int(mjesec);
//		_godina = new int(godina);
//		_sati = new int(sati);
//		_minuti = new int(minuti);
//	}
//	~DatumVrijeme() {
//		delete _dan; _dan = nullptr;
//		delete _mjesec; _mjesec = nullptr;
//		delete _godina; _godina = nullptr;
//		delete _sati; _sati = nullptr;
//		delete _minuti; _minuti = nullptr;
//	}
//	DatumVrijeme(const DatumVrijeme& obj)
//	{
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		_sati = new int(*obj._sati);
//		_minuti = new int(*obj._minuti);
//	}
//	DatumVrijeme& operator=(const DatumVrijeme& obj)
//	{
//		if (this==&obj)
//		{
//			return *this;
//		}
//		_dan = new int(*obj._dan);
//		_mjesec = new int(*obj._mjesec);
//		_godina = new int(*obj._godina);
//		_sati = new int(*obj._sati);
//		_minuti = new int(*obj._minuti);
//			return *this;
//	}
//	char* ToCharArray() {
//		stringstream temp ;
//		temp << *_dan << "." << *_mjesec << "." << *_godina << " " << *_sati << ":" << *_minuti << "\n";
//		return AlocirajNizKaraktera(temp.str().c_str());
//	}
//	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
//		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
//		return COUT;
//	}
//	int toSekunde() {
//		return *_dan * 24 * 60 * 60 + *_mjesec * 30 * 24 * 60 * 60 + *_godina * 365 * 24 * 60 * 60 + *_sati * 60 * 60 + *_minuti * 60;
//	}
//
//	bool operator == (const DatumVrijeme& d) {
//		return
//			*_dan == *d._dan &&
//			*_mjesec == *d._mjesec &&
//			*_godina == *d._godina &&
//			*_sati == *d._sati &&
//			*_minuti == *d._minuti;
//	}
//};
//
//class Predmet {
//	char* _naziv;
//	int _ocjena;
//	string _napomena;
//public:
//	Predmet(const char* naziv, int ocjena, string napomena = "") :_ocjena(ocjena), _napomena(napomena) {
//		_naziv = AlocirajNizKaraktera(naziv);
//	}
//
//	Predmet(const Predmet& obj)
//	{
//		_ocjena = obj._ocjena;
//		_napomena = obj._napomena;
//		_naziv = AlocirajNizKaraktera(obj._naziv);
//	}
//	Predmet& operator=(const Predmet& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_ocjena = obj._ocjena;
//		_napomena = obj._napomena;
//		_naziv = AlocirajNizKaraktera(obj._naziv);
//			return *this;
//	}
//	~Predmet() {
//		delete[] _naziv; _naziv = nullptr;
//	}
//	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
//		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
//		return COUT;
//	}
//	char* GetNaziv() { return _naziv; }
//	string GetNapomena() { return _napomena; }
//	void DodajNapomenu(string napomena) {
//		_napomena += " " + napomena;
//	}
//	int getOcjena() { return _ocjena; }
//
//	bool operator==(Predmet predmet)
//	{
//		return strcmp(_naziv, predmet._naziv) == 0;
//	}
//
//};
//
//class Uspjeh {
//	eRazred _razred;
//	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
//	Kolekcija<Predmet*, DatumVrijeme>* _predmeti;
//public:
//	Uspjeh(eRazred razred) :_razred(razred), _predmeti(nullptr) {
//	}
//	~Uspjeh() {
//		for (size_t i = 0; i < _predmeti->getTrenutno(); i++)
//			delete _predmeti->getElement1(i);
//		delete _predmeti; _predmeti = nullptr;
//	}
//	Uspjeh(Uspjeh & u) :Uspjeh(u._razred) {
//		_predmeti = new Kolekcija<Predmet*, DatumVrijeme>;
//		if (u.GetPredmeti() != nullptr) {
//			for (size_t i = 0; i < u.GetPredmeti()->getTrenutno(); i++)
//			{
//				_predmeti->AddElement(new Predmet(*u.GetPredmeti()->getElement1(i)), u.GetPredmeti()->getElement2(i));
//			}
//		}
//	}
//
//	Kolekcija<Predmet*, DatumVrijeme>* GetPredmeti() { return _predmeti; }
//	eRazred getRazredi() { return _razred; }
//
//	friend ostream& operator<< (ostream & COUT, Uspjeh & obj) {
//		COUT << obj._razred << " RAZRED: " << crt;
//		if (obj._predmeti != nullptr) {
//			for (size_t i = 0; i < obj._predmeti->getTrenutno(); i++)
//				cout << *obj._predmeti->getElement1(i) << " " << obj.GetPredmeti()->getElement2(i) << endl;
//		}
//		return COUT;
//	}
//	void dodajPredmet(Predmet p, DatumVrijeme d) {
//		if (_predmeti == nullptr) _predmeti = new Kolekcija<Predmet*, DatumVrijeme>;
//		_predmeti->AddElement(new Predmet(p), d);
//	}
//};
//
//
//class Kandidat {
//	char* _imePrezime;
//	string _emailAdresa;
//	string _brojTelefona;
//	vector<Uspjeh*> _uspjeh;
//public:
//	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) :_emailAdresa(emailAdresa), _brojTelefona(brojTelefona) {
//		_imePrezime = AlocirajNizKaraktera(imePrezime);
//	}
//	Kandidat(const Kandidat& obj)
//	{
//		_emailAdresa = obj._emailAdresa;
//		_brojTelefona = obj._brojTelefona;
//		_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
//		_uspjeh = obj._uspjeh;
//	}
//	Kandidat& operator=(const Kandidat& obj)
//	{
//		if (&obj==this)
//		{
//			return *this;
//		}
//		_emailAdresa = obj._emailAdresa;
//		_brojTelefona = obj._brojTelefona;
//		_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
//		_uspjeh = obj._uspjeh;
//		return *this;
//	}
//
//	~Kandidat() {
//		delete[] _imePrezime; _imePrezime = nullptr;
//		for (size_t i = 0; i < _uspjeh.size(); i++) {
//			delete _uspjeh[i];
//			_uspjeh[i] = nullptr;
//		}
//	}
//	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
//		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
//		for (size_t i = 0; i < obj._uspjeh.size(); i++)
//			COUT << *obj._uspjeh[i] << endl;
//		return COUT;
//	}
//	vector<Uspjeh*> GetUspjeh() { return _uspjeh; }
//
//	bool AddPredmet(eRazred razred, Predmet predmet, DatumVrijeme& datumVrijeme)
//	{
//		for (vector<Uspjeh*>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
//		{
//			if ((*i)->getRazredi() == razred)
//			{
//				if ((*i)->GetPredmeti()->getTrenutno() >= 6)
//				{
//					cout << "Vec postoji 6 predmeta" << endl;
//					return false;
//				}
//				for (size_t j = 0; j < (*i)->GetPredmeti()->getTrenutno(); j++)
//				{
//					if (*(*i)->GetPredmeti()->getElement1(j) == predmet || (*i)->GetPredmeti()->getElement2(j) == datumVrijeme)
//					{
//						cout << "Vec je dodan taj predmet/datum" << endl;
//						return false;
//					}
//				}
//				for (size_t z = 0; z < ((*i)->GetPredmeti()->getTrenutno()); z++)
//				{
//					if (datumVrijeme.toSekunde() - (*i)->GetPredmeti()->getElement2(z).toSekunde() <= 60)
//					{
//						cout << "Nije proslo vise od minute od zadnjeg dodavanja" << endl;
//						return false;
//					}
//				}
//				/*pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
//				upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
//				sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od minimalan_prosjek
//				kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova implemenitrati koristeci
//				zasebne thread-ove.
//				*/
//				if ((*i)->GetPredmeti()->getTrenutno() == 6)
//				{
//					thread email([&]() {
//						cout << "Evidentirali ste uspjeh za " << razred << ". razred." << endl;
//						float prosjek = 0;
//						for (size_t z = 0; z < (*i)->GetPredmeti()->getTrenutno(); z++)
//						{
//							prosjek += (*i)->GetPredmeti()->getElement1(z)->getOcjena();
//						}
//						prosjek /= float((*i)->GetPredmeti()->getTrenutno());
//						if (prosjek > minimalan_prosjek)
//						{
//							thread sms([prosjek]() {
//								m.lock();
//								cout << "Svaka cast za uspjeh " << prosjek << endl;
//								m.unlock();
//								});
//							sms.join();
//						}
//						});
//					email.join();
//				}
//
//
//			}
//		}
//
//		Uspjeh* tempUspjeh = new Uspjeh(razred);
//		tempUspjeh->dodajPredmet(predmet, datumVrijeme);
//		_uspjeh.push_back(tempUspjeh);
//		return true;
//
//	}
//
//	Uspjeh* operator()(eRazred razred) {
//		for (vector<Uspjeh*>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
//		{
//			if ((*i)->getRazredi() == razred)
//			{
//				
//				return *i;
//			}
//		}
//	}
//
//
//};
//
//void main() {
//	/****************************************************************************
//	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
//	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
//	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
//	4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
//	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
//	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
//	****************************************************************************/
//
//#pragma region DatumIKolekcija
//	DatumVrijeme temp,
//		datum19062018_1015(19, 6, 2018, 10, 15),
//		datum20062018_1115(20, 6, 2018, 11, 15),
//		datum30062018_1215(30, 6, 2018, 12, 15),
//		datum05072018_1231(5, 7, 2018, 12, 31),
//		datum20062018_1115_Copy(datum20062018_1115);
//	//funkcija ToCharArray vraca datum i vrijeme kao char *
//	cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15
//	temp = datum05072018_1231;
//	cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
//	cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15
//
//	const int kolekcijaTestSize = 10;
//	Kolekcija<int, int> kolekcija1;
//	for (size_t i = 0; i < kolekcijaTestSize; i++)
//		kolekcija1.AddElement(i + 1, i * i);
//	cout << kolekcija1 << endl;
//
//	Kolekcija<int, int> kolekcija2 = kolekcija1;
//	cout << kolekcija2 << crt;
//	Kolekcija<int, int> kolekcija3;
//	kolekcija3 = kolekcija1;
//	kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
//	cout << kolekcija3 << crt;
//#pragma endregion
//
//	//napomena se moze dodati i prilikom kreiranja objekta
//	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
//		Fizika("Fizika", 5),
//		Hemija("Hemija", 2),
//		Engleski("Engleski", 5);
//	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
//	cout << Fizika << endl;
//
//	Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
//	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
//
//	/*
//	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
//	tom prilikom onemoguciti:
//	- dodavanje vise od 6 predmeta za jedan razred
//	- dodavanje istoimenih predmeta na nivou jednog razreda,
//	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje minut).
//	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
//	razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
//	*/
//	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
//		cout << "Predmet uspjesno dodan!" << crt;
//	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
//		cout << "Predmet uspjesno dodan!" << crt;
//	if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
//		cout << "Predmet uspjesno dodan!" << crt;
//	if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
//		cout << "Predmet uspjesno dodan!" << crt;
//	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
//	if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
//		cout << "Predmet uspjesno dodan!" << crt;
//	//ne treba dodati Fiziku jer nije prosao minut od dodavanja posljednjeg predmeta
//	/*if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
//		cout << "Predmet uspjesno dodan!" << crt;*/
//	/*pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
//	upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
//	sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od minimalan_prosjek
//	kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova implemenitrati koristeci
//	zasebne thread-ove.
//	*/
//
//	Uspjeh * u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
//	if (u != nullptr)
//		cout << *u << endl;
//
//
//	system("pause");
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////nedovrsen
////#include <iostream>
////#include <string>
////#include <vector>
////#include <regex>
////#include <thread>
////#include <mutex>
////using namespace std;
////
////const char* crt = "\n_________________________\n";
////mutex m;
////
////class Datum {
////	int* _dan, * _mjesec, * _godina;
////public:
////	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
////		_dan = new int(dan);
////		_mjesec = new int(mjesec);
////		_godina = new int(godina);
////	}
////	Datum(const Datum& dat) {
////		_dan = new int(*dat._dan);
////		_mjesec = new int(*dat._mjesec);
////		_godina = new int(*dat._godina);
////	}
////	Datum& operator=(const Datum& dat)
////	{
////		if (this==&dat)
////		{
////			return *this;
////		}
////		_dan = new int(*dat._dan);
////		_mjesec = new int(*dat._mjesec);
////		_godina = new int(*dat._godina);
////		return *this;
////	}
////	~Datum() {
////		delete _dan; _dan = nullptr;
////		delete _mjesec; _mjesec = nullptr;
////		delete _godina; _godina = nullptr;
////	}
////	friend ostream& operator<<(ostream& COUT, const Datum& obj) {
////		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
////		return COUT;
////	}
////	int toDani() {
////		return *_dan + *_mjesec * 30 + *_godina * 365;
////	}
////};
////class Izuzetak : public exception {
////	string _funkcija;
////public:
////	Izuzetak(string poruka,string funkcija):exception(poruka.c_str()),_funkcija(funkcija)
////	{}
////	friend ostream& operator<<(ostream& cout, const Izuzetak& izuzetak)
////	{
////		cout << "Greska " << izuzetak.what() << " u funkciji " << izuzetak._funkcija << endl;
////		return cout;
////	}
////};
////
////template <class T1, class T2>
////class Kolekcija {
////	T1* _elementi1;
////	T2* _elementi2;
////	int _trenutnoElemenata;
////	bool _omoguciDupliranjeElemenata;
////public:
////	Kolekcija(bool omoguciDupliranjeElemenata = false) {
////		_trenutnoElemenata = 0;
////		_omoguciDupliranjeElemenata = omoguciDupliranjeElemenata;
////		_elementi1 = nullptr;
////		_elementi2 = nullptr;
////	}
////
////	Kolekcija(const Kolekcija& obj)
////	{
////		_elementi1 = new T1[obj._trenutnoElemenata];
////		_elementi2 = new T2[obj._trenutnoElemenata];
////		for (size_t i = 0; i < obj.GetTrenutno(); i++)
////		{
////			_elementi1[i] = obj.GetElement1(i);
////			_elementi2[i] = obj.GetElement2(i);
////		}
////		_trenutnoElemenata = obj._trenutnoElemenata;
////		_omoguciDupliranjeElemenata = obj._omoguciDupliranjeElemenata;
////	}
////	
////	Kolekcija& operator=(const Kolekcija& obj)
////	{
////		if (this==&obj)
////		{
////			return *this;
////		}
////		_elementi1 = new T1[obj._trenutnoElemenata];
////		_elementi2 = new T2[obj._trenutnoElemenata];
////		for (size_t i = 0; i < obj.GetTrenutno(); i++)
////		{
////			_elementi1[i] = obj.GetElement1(i);
////			_elementi2[i] = obj.GetElement2(i);
////		}
////		_trenutnoElemenata = obj._trenutnoElemenata;
////		_omoguciDupliranjeElemenata = obj._omoguciDupliranjeElemenata;
////			return *this;
////	}
////
////
////	~Kolekcija() {
////		delete[]_elementi2; _elementi2 = nullptr;
////		delete[]_elementi1; _elementi1 = nullptr;
////		_trenutnoElemenata = 0;
////	}
////
////	bool AddElement(const T1& element1, const T2& element2) {
////		if (!_omoguciDupliranjeElemenata)
////		{
////			for (size_t i = 0; i < _trenutnoElemenata; i++)
////			{
////				if (_elementi1[i]==element1 && _elementi2[i]==element2)
////				{
////					cout << "Vec postoji element/i" << endl;
////					return false;
////				}
////			}
////		}
////
////		T1* temp1 = new T1[_trenutnoElemenata + 1];
////		T2* temp2 = new T2[_trenutnoElemenata + 1];
////		for (size_t i = 0; i < _trenutnoElemenata; i++)
////		{
////			temp1[i] = _elementi1[i];
////			temp2[i] = _elementi2[i];
////		}
////		delete[]_elementi1;
////		delete[]_elementi2;
////		_elementi1 = temp1;
////		_elementi2=temp2;
////		_elementi1[_trenutnoElemenata] = element1;
////		_elementi2[_trenutnoElemenata] = element2;
////		_trenutnoElemenata++;
////		return true;
////
////	}
////	void RemoveElement(const T1& element1) {
////		int index = -1;
////		for (size_t i = 0; i < _trenutnoElemenata; i++)
////		{
////			if (_elementi1[i]==element1)
////			{
////				index = i;
////				break;
////			}
////		}
////		if (index<0)
////		{
////			cout << "Ne postoji taj element" << endl;
////			return;
////		}
////		T1* temp1 = new T1[_trenutnoElemenata - 1];
////		T2* temp2 = new T2[_trenutnoElemenata - 1];
////		int j = 0;
////		for (size_t i = 0; i < _trenutnoElemenata; i++)
////		{
////			if (index==i)
////			{
////				j++;
////			}
////			temp1[i] = _elementi1[j];
////			temp2[i] = _elementi2[j];
////			j++;
////		}
////		delete[]_elementi1;
////		delete[]_elementi2;
////		_elementi1 = temp1;
////		_elementi2 = temp2;
////		_trenutnoElemenata--;
////	}
////
////	int GetTrenutno() const { return _trenutnoElemenata; }
////	T1& GetElement1(int lokacija) const
////	{
////		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
////			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
////		return _elementi1[lokacija];
////	}
////
////	T2& GetElement2(int lokacija) const
////	{
////		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
////			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
////		return _elementi2[lokacija];
////	}
////
////	void setElement2(T2 element2,int lokacija)
////	{
////		_elementi2[lokacija] = element2;
////	}
////
////	friend ostream& operator<<(ostream & COUT, const Kolekcija & obj) {
////		for (size_t i = 0; i < obj.GetTrenutno(); i++)
////			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
////		return COUT;
////	}
////};
////
////class Dogadjaj
////{
////	Datum _datumOdrzavanja;
////	Kolekcija<string, bool>* _obaveze; //cuva informaciju o obavezama koje je potrebno ispuniti prije samog dogadjaja, 
////	//string se odnosi na opis, a bool na izvrsenje te obaveze (da li je zavrsena ili ne)
////
////	char* _naziv;
////	int _notificirajPrije; //oznacava broj dana prije samog dogadjaja kada ce krenuti notifikacija/podsjetnik
////	bool _rekurzivnaNotifikacija; //ako je vrijednost true onda se korisnik notificira svaki dan do _datumaOdrzavanja dogadjaja, a pocevsi prije dogadjaja za _brojDanaZaNotifikaciju
////
////
////	bool isValidnaObaveza(string obaveza)
////	{
////		regex pravilo("ubiti|sakriti");
////		return regex_search(obaveza, pravilo);
////	}
////
////public:
////	Dogadjaj(Datum datumOdrzavanja, const char* naziv, int brojDana = 1,
////		bool rekurzivnaNotifikacija = false) : _datumOdrzavanja(datumOdrzavanja)
////	{
////		_naziv = new char[strlen(naziv) + 1];
////		strcpy_s(_naziv, strlen(naziv) + 1, naziv);
////
////		_notificirajPrije = brojDana;
////		_rekurzivnaNotifikacija = rekurzivnaNotifikacija;
////		_obaveze = nullptr;
////	}
////
////	Dogadjaj(const Dogadjaj& obj) : _datumOdrzavanja(obj._datumOdrzavanja)
////	{
////		_naziv = new char[strlen(obj._naziv) + 1];
////		strcpy_s(_naziv, strlen(obj._naziv) + 1, obj._naziv);
////
////		_notificirajPrije = obj._notificirajPrije;
////		_rekurzivnaNotifikacija = obj._rekurzivnaNotifikacija;
////		_obaveze = new Kolekcija<string, bool>;
////		*_obaveze = *obj._obaveze;
////	}
////	
////	Dogadjaj& operator=(const Dogadjaj& obj)
////	{
////		if (this==&obj)
////		{
////			return *this;
////		}
////		_datumOdrzavanja = obj._datumOdrzavanja;
////		_naziv = new char[strlen(obj._naziv) + 1];
////		strcpy_s(_naziv, strlen(obj._naziv) + 1, obj._naziv);
////
////		_notificirajPrije = obj._notificirajPrije;
////		_rekurzivnaNotifikacija = obj._rekurzivnaNotifikacija;
////		_obaveze = new Kolekcija<string, bool>;
////		*_obaveze = *obj._obaveze;
////		return *this;
////	}
////
////	~Dogadjaj()
////	{
////		delete[] _naziv;
////		_naziv = nullptr;
////		delete _obaveze;
////		_obaveze = nullptr;
////	}
////
////	bool AddObavezu(string novaObaveza)
////	{
////		if (_obaveze==nullptr)
////		{
////			_obaveze = new Kolekcija<string, bool>;
////		}
////		if (isValidnaObaveza(novaObaveza))
////		{
////			throw Izuzetak("u tekstu postoje zabranjene rijeci", __FUNCTION__);
////		}
////		return _obaveze->AddElement(novaObaveza, false);
////	}
////
////	bool operator==(Dogadjaj& dogadjaj) {
////		return strcmp(_naziv, dogadjaj._naziv) == 0;
////	}
////
////	Datum getDatum() {
////		return _datumOdrzavanja;
////	}
////	char* GetNaziv() { return _naziv; }
////	Kolekcija<string, bool>* GetObaveze() { return _obaveze; }
////
////};
////
////class Student
////{
////	int _indeks;
////	string _imePrezime;
////	vector<Dogadjaj> _dogadjaji;
////public:
////
////	Student(int indeks, string imePrezime) : _indeks(indeks), _imePrezime(imePrezime) {}
////
////	int GetIndeks() const { return _indeks; }
////
////	bool AddDogadjaj( Dogadjaj& noviDogadjaj) {
////		for (vector<Dogadjaj>::iterator i = _dogadjaji.begin(); i != _dogadjaji.end(); i++)
////		{
////			if (*i==noviDogadjaj)
////			{
////				return false;
////			}
////		}
////		_dogadjaji.push_back(noviDogadjaj);
////		return true;
////	}
////
////	bool operator==(Student& student)
////	{
////		if (_indeks==student._indeks)
////		{
////			return true;
////		}
////		return false;
////	}
////
////	vector<Dogadjaj>& GetDogadjaji() { return _dogadjaji; }
////
////	string getIme() {
////		return _imePrezime;
////	}
////
////	friend ostream& operator<<(ostream& COUT, const Student& obj)
////	{
////		COUT << obj._imePrezime << " (" << obj._indeks << ")" << endl;
////		return COUT;
////	}
////};
////
////class DLWMSReminder
////{
////	vector<Student> _reminiderList;
////public:
////	bool AddStudent(Student& noviStudent) {
////		for (vector<Student>::iterator i = _reminiderList.begin(); i != _reminiderList.end(); i++)
////		{
////			if (*i == noviStudent) {
////				throw Izuzetak("Vec postoji taj student!" , __FUNCTION__);
////			}
////		}
////		_reminiderList.push_back(noviStudent);
////		return true;
////	}
////
////	bool OznaciObavezuKaoZavrsenu(int indeks, const char* nazivDogadjaja, string nazivObaveze) {
////		for (vector<Student>::iterator i = _reminiderList.begin(); i != _reminiderList.end(); i++)
////		{
////			if (i->GetIndeks()==indeks)
////			{
////				for (vector<Dogadjaj>::iterator j = i->GetDogadjaji().begin(); j != i->GetDogadjaji().end(); j++)
////				{
////					if (strcmp(j->GetNaziv(),nazivDogadjaja)==0)
////					{
////						for (size_t k = 0; k < j->GetObaveze()->GetTrenutno(); k++)
////						{
////							if (j->GetObaveze()->GetElement1(k)==nazivObaveze && j->GetObaveze()->GetElement2(k)==false)
////							{
////								j->GetObaveze()->setElement2(true,k);
////								return true;
////							}
////						}
////					}
////				}
////			}
////		}
////		return false;
////	}
////
////	/*metodi PosaljiNotifikacije se salje trenutni datum na osnovu cega ona pretrazuje sve studente koje treba podsjetiti/notificirati o dogadjajima koji se priblizavaju.
////	Koristeci multithread-ing, svim studentima se salju notifikacije sa sljedecim sadrzajem:
////	-------------------------------------------------------------------------
////	Postovani Jasmin Azemovic,
////	Dogadjaj Ispit iz PRIII je zakazan za 3 dana, a do sada ste obavili 56% obaveza vezanih za ovaj dogadjaj. Neispunjene obaveze su:
////	1.Preraditi ispitne zadatke
////	2.Samostalno vjezbati
////	Predlazemo Vam da ispunite i ostale planirane obaveze.
////	FIT Reminder
////	-------------------------------------------------------------------------
////	Dakle, notifikacije ce biti poslane svim studentima koji su dodali dogadjaj za 30.01.2018. godine i
////	oznacili da zele da budu podsjecani ponovo/rekurzivno najmanje 2 dana prije samog dogadjaja (podaci se odnose na konkretan dogadjaj: Ispit iz PRIII)
////	*/
////
////	int PosaljiNotifikacije(Datum datum) {
////		int brojac = 0;
////		for (vector<Student>::iterator i = _reminiderList.begin(); i != _reminiderList.end(); i++)
////		{
////			for (vector<Dogadjaj>::iterator j = i->GetDogadjaji().begin(); j!= i->GetDogadjaji().end(); j++)
////			{
////				if (j->getDatum().toDani() > datum.toDani())
////				{
////					thread send([&] {
////						brojac++;
////						int preostaloDana = (j->getDatum().toDani() - datum.toDani());
////						string temporarni = "";
////						temporarni += "Postovani " + i->getIme() + "\nDogadjaj " + j->GetNaziv() + " je zakazan za " + to_string(preostaloDana) +
////							" dana,a do sada ste obavili " + to_string([j]()->int {
////							int brojac = 0;
////							for (size_t i = 0; i < j->GetObaveze()->GetTrenutno(); i++)
////							{
////								if (j->GetObaveze()->GetElement2(i))
////								{
////									brojac++;
////								}
////							}
////							return brojac*100 / (j->GetObaveze()->GetTrenutno());
////								}()) + "% obaveza vezanih za ovaj dogadjaj.Neispunjene obaveze su: " + "\n"
////							+([&]()->string {
////							int interniBrojac = 1;
////							string temp = "";
////							for (size_t k = 0; k < j->GetObaveze()->GetTrenutno(); k++)
////							{
////								if (j->GetObaveze()->GetElement2(k) == false)
////								{
////									temp += to_string(interniBrojac) + j->GetObaveze()->GetElement1(k) + "\n";
////									interniBrojac++;
////								}
////							}
////							return temp;
////								}()) + "Predlazemo Vam da ispunite i ostale planirane obaveze.\nFIT Reminder" + crt;
////						cout << temporarni;
////						});
////					send.join();
////				}
////			}
////		}
////		return brojac;
////	}
////};
////
////void main() {
////
////	/**************************************************************************
////	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
////	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
////	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
////	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_ParcijalniII.TXT
////	5. NAZIVI FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI PO ŽELJI.
////	****************************************************************************/
////
////#pragma region Datum
////
////	Datum danas(28, 1, 2018), sutra(29, 1, 2018);
////	Datum datumIspitaPRIII(30, 1, 2018), datumIspitBPII(31, 1, 2018);
////	Datum prekosutra(danas);
////	prekosutra = danas;
////	cout << danas << endl
////		<< sutra << endl
////		<< prekosutra << crt;
////
////#pragma endregion
////
////#pragma region Kolekcija
////
////	/*
////	AddElement :: omogucava dodavanje novog elementa u kolekciju.
////	Ukoliko je moguce, osigurati automatsko prosiranje kolekcije prilikom dodavanja svakog novog elementa, te onemoguciti ponavljanje elemenata
////	RemoveElement :: na osnovu parametra tipa T1 uklanja elemente iz kolekcije i ukoliko je moguce smanjuje 
////	velicinu niza/kolekcije. Prilikom uklanjanja elemenata ocuvati redoslijed njihovog dodavanja
////	*/
////	const int brElemenata = 10;
////	Kolekcija<int, float> kolekcija1;
////	for (size_t i = 0; i < brElemenata; i++)
////		if (!kolekcija1.AddElement(i, i + (0.6 * i)))
////			cout << "Elementi " << i << " i " << i + (0.6 * i) << " nisu dodati u kolekciju" << endl;
////
////	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
////	cout << kolekcija1 << endl;
////
////	kolekcija1.RemoveElement(5);
////
////	Kolekcija<int, float> kolekcija2;
////	kolekcija2 = kolekcija1;
////	cout << kolekcija2 << crt;
////
////	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
////		cout << "ISTI BROJ ELEMENATA" << endl;
////
////	Kolekcija<int, float> kolekcija3(kolekcija2);
////	cout << kolekcija3 << crt;
////
////#pragma endregion
////
////#pragma region Dogadjaj
////
////	Dogadjaj ispitPRIII(datumIspitaPRIII, "Ispit iz PRIII", 5, true),
////		ispitBPII(datumIspitBPII, "Ispit iz BPII", 7, true);
////	/*po vlasitom izboru definisati listu zabranjenih rijeci koje ce onemoguciti dodavanje odredjene obaveze. Prilikom provjere koristiti regex*/
////	if (ispitPRIII.AddObavezu("Preraditi pdf materijale"))cout << "Obaveza dodana!" << endl;
////	//onemoguciti dupliranje obaveza
////	if (!ispitPRIII.AddObavezu("Preraditi pdf materijale"))cout << "Obaveza nije dodana!" << endl;
////	if (ispitPRIII.AddObavezu("Pregledati video materijale"))cout << "Obaveza dodana!" << endl;
////	if (ispitPRIII.AddObavezu("Preraditi ispitne zadatke"))cout << "Obaveza dodana!" << endl;
////	if (ispitPRIII.AddObavezu("Samostalno vjezbati"))cout << "Obaveza dodana!" << endl;
////
////	if (ispitBPII.AddObavezu("Preraditi knjigu SQL za 24 h"))cout << "Obaveza dodana!" << endl;
////	if (ispitBPII.AddObavezu("Pregledati video materijale"))cout << "Obaveza dodana!" << endl;
////	if (ispitBPII.AddObavezu("Napraviti bazu za konkretnu aplikaciju"))cout << "Obaveza dodana!" << endl;
////	/*try
////	{
////		ispitBPII.AddObavezu("sakriti papire");
////
////	}
////	catch (Izuzetak& iz)
////	{
////		cout << iz << endl;
////	}*/
////
////	Student jasmin(150051, "Jasmin Azemovic"), adel(160061, "Adel Handzic");
////
////	if (jasmin.AddDogadjaj(ispitPRIII) && jasmin.AddDogadjaj(ispitBPII))
////		cout << "Dogadjaj uspjesno dodan!" << endl;
////
////	if (adel.AddDogadjaj(ispitPRIII) && adel.AddDogadjaj(ispitBPII))
////		cout << "Dogadjaj uspjesno dodan!" << endl;
////	//onemoguciti dupliranje dogadjaja
////	if (!adel.AddDogadjaj(ispitPRIII))
////		cout << "Dogadjaj nije uspjesno dodan!" << endl;
////
////	cout << crt;
////
////	DLWMSReminder reminder;
////
////	try
////	{
////		reminder.AddStudent(jasmin);
////		reminder.AddStudent(adel);
////		//u slucaju dupliranja studenata funkcija baca izuzetak tipa Izuzetak
////		reminder.AddStudent(jasmin);
////	}
////	catch (Izuzetak & err)
////	{
////		//ispisati sve informacije o nastalom izuzetku
////		cout << err << endl;
////	}
////
////	//da bi bila oznacena kao zavrsena, obaveza mora postojati i mora biti oznacena kao nezavrsena (false)
////	if (reminder.OznaciObavezuKaoZavrsenu(150051, "Ispit iz PRIII", "Pregledati video materijale"))
////		cout << "Obaveza oznacena kao zavrsena" << endl;
////
////	/*metodi PosaljiNotifikacije se salje trenutni datum na osnovu cega ona pretrazuje sve studente koje treba podsjetiti/notificirati o dogadjajima koji se priblizavaju.
////	Koristeci multithread-ing, svim studentima se salju notifikacije sa sljedecim sadrzajem:
////	-------------------------------------------------------------------------
////	Postovani Jasmin Azemovic,
////	Dogadjaj Ispit iz PRIII je zakazan za 3 dana, a do sada ste obavili 56% obaveza vezanih za ovaj dogadjaj. Neispunjene obaveze su:
////	1.Preraditi ispitne zadatke
////	2.Samostalno vjezbati
////	Predlazemo Vam da ispunite i ostale planirane obaveze.
////	FIT Reminder
////	-------------------------------------------------------------------------
////	Dakle, notifikacije ce biti poslane svim studentima koji su dodali dogadjaj za 30.01.2018. godine i 
////	oznacili da zele da budu podsjecani ponovo/rekurzivno najmanje 2 dana prije samog dogadjaja (podaci se odnose na konkretan dogadjaj: Ispit iz PRIII)
////	*/
////	int poslato = 0;
////	//funkcija vraca broj poslatih podsjetnika/notifikacija
////	poslato = reminder.PosaljiNotifikacije(danas);
////	cout << "Za " << danas << " poslato ukupno " << poslato << " podsjetnika!" << endl;
////	poslato = reminder.PosaljiNotifikacije(sutra);
////	cout << "Za " << sutra << " poslato ukupno " << poslato << " podsjetnika!" << endl;
////
////#pragma endregion
////
////	system("pause");
////}