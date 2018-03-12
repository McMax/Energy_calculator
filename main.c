#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

const double proton_mass = 0.938272013; //GeV/c^2
const double nucleon_mass = 0.9389186795; //GeV/c^2
const double neutron_mass = 0.939565346; //GeV/c^2

using namespace std;

int menu(double&, int&, int&, int&, int&, string&);

int main()
{
	double b_momentum;
	int beam_protons, beam_neutrons, target_protons, target_neutrons;
	string system_str;

	int answer = menu(b_momentum, beam_protons, beam_neutrons, target_protons, target_neutrons, system_str);
	if(answer != 0)
	{
		return answer;
	}

	cout << system_str << "@" << b_momentum << endl;
	cout << "===================================" << endl;
	cout << "===================================" << endl;
	cout << "    Assuming asymmetric system" << endl;
	cout << " beam protons: " << beam_protons << endl;
	cout << " beam neutrons: " << beam_neutrons << endl;
	cout << " target protons: " << target_protons << endl;
	cout << " target neutrons: " << target_neutrons << endl;
	cout << " proton mass: " << proton_mass << endl;
	cout << " neutron mass: " << neutron_mass << endl;
	cout << "===================================" << endl;

	double total_beam_momentum = b_momentum*(beam_protons+beam_neutrons);

	double beam_mass = beam_protons*proton_mass + beam_neutrons*neutron_mass;
	double target_mass = target_protons*proton_mass + target_neutrons*neutron_mass;

	double beam_energy = sqrt(total_beam_momentum*total_beam_momentum + beam_mass*beam_mass);

	double beta = total_beam_momentum/(beam_energy+target_mass);
	double gamma = (1/(sqrt(1-pow(beta,2))));

	double y_cms = 0.5*log((1+beta)/(1-beta));

	double sqrtsnn = sqrt(beam_mass*beam_mass+target_mass*target_mass+2*beam_energy*target_mass);

	cout << "Total beam mass : " << beam_mass << endl;
	cout << "Total target mass : " << target_mass << endl;
	cout << "Total beam momentum (p_tot): " << total_beam_momentum << endl;
	cout << "Total beam energy (E_beam): " << beam_energy << endl;
	cout << "sqrt(s_NN) = " << sqrtsnn << endl;
	cout << "Beta: " << beta << endl;
	cout << "Gamma: " << gamma << endl;
	cout << "Rapidity of c.m. system in LAB frame: " << y_cms << endl << endl;

	int beam_nucleons = beam_protons+beam_neutrons;
	int target_nucleons = target_protons+target_neutrons;

	cout << "===================================" << endl;
	cout << "===================================" << endl;
	cout << "       Nucleon simplification      " << endl;
	cout << " beam nucleons " << beam_nucleons << endl;
	cout << " target nucleons " << target_nucleons << endl;
	cout << " nucleon mass " << nucleon_mass << endl;
	cout << "===================================" << endl;

	total_beam_momentum = b_momentum*beam_nucleons;

	beam_mass = beam_nucleons*nucleon_mass;
	target_mass = target_nucleons*nucleon_mass;

	beam_energy = sqrt(total_beam_momentum*total_beam_momentum + beam_mass*beam_mass);

	beta = total_beam_momentum/(beam_energy+target_mass);
	gamma = (1/(sqrt(1-pow(beta,2))));
	y_cms = 0.5*log((1+beta)/(1-beta));

	sqrtsnn = sqrt(beam_mass*beam_mass+target_mass*target_mass+2*beam_energy*target_mass);

	cout << "Total beam mass : " << beam_mass << endl;
	cout << "Total target mass : " << target_mass << endl;
	cout << "Total beam momentum (p_tot): " << total_beam_momentum << endl;
	cout << "Total beam energy (E_beam): " << beam_energy << endl;
	cout << "sqrt(s_NN) = " << sqrtsnn << endl;
	cout << "Beta: " << beta << endl;
	cout << "Gamma: " << gamma << endl;
	cout << "Rapidity of c.m. system in LAB frame: " << y_cms << endl << endl;
	
	return 0;
}

int menu(double &b_momentum, int &beam_protons, int &beam_neutrons, int &target_protons, int &target_neutrons, string &system_str)
{
	int choice;
	char buffer[10];

	cout << "Choose system" << endl;
	cout << "=============" << endl;
	cout << "1. p+p" << endl;
	cout << "2. Be+Be" << endl;
	cout << "3. Ar+Sc" << endl;
	cout << "4. Xe+La" << endl;
	cout << "5. Pb+Pb" << endl;
	cout << "?: ";
	cin >> buffer;
	cout << endl;
	choice = atoi(buffer);

	switch(choice)
	{
		case 1:
		{//p+p
			system_str = "p+p";
			beam_protons = target_protons = 1;
			beam_neutrons = target_neutrons = 0;
			break;
		}
		case 2:
		{//7Be+9Be
			system_str = "Be+Be";
			beam_protons = target_protons = 4;
			beam_neutrons = 3;
			target_neutrons = 5;
			break;
		}
		case 3:
		{//40Ar+45Sc
			system_str = "Ar+Sc";
			beam_protons = 18;
			beam_neutrons = (40-beam_protons);
			target_protons = 21;
			target_neutrons = (45-target_protons);
			break;
		}
		case 4:
		{//129Xe+135La
			system_str = "Xe+La";
			beam_protons = 54;
			beam_neutrons = (129-beam_protons);
			target_protons = 57;
			target_neutrons = (135-target_protons);
			break;
		}
		case 5:
		{//208Pb+208Pb
			system_str = "Pb+Pb";
			beam_protons = target_protons = 82;
			beam_neutrons = target_neutrons = (208-target_protons);
			break;
		}
		default:
		{
			cout << "Error. Choose system by entering number 1-5" << endl;
			return 1;
		}
	}

	cout << "Enter beam momentum per nucleon" << endl;
	cout << "?: ";
	cin >> buffer;
	cout << endl;
	b_momentum = atof(buffer);
	if(b_momentum < 0)
	{
		cout << "Error. Enter proper beam momentum" << endl;
		return 2;
	}

	return 0;
}
