#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

class Card {
private:
	int nbr, bjv;
	string c, s;

public:
	Card(int number, int bjVal, string crd, string suite)
	 : nbr(number), bjv(bjVal), c(crd), s(suite) {

	}


	void printCard() {
		cout << "card #" << nbr << ", " << c << " of " << s <<"s (" << c[0] << s[0] << "), BJ Value - " << bjv << endl;
	}

	string cardname() {
		return c +" of " + s;
	}

	int BJValue() {
		return bjv;
	}
};

class Player {
private:
	int value, aces;
public:
	Player()
	 :value(0), aces(0) {

	}
	void setValue(int val) {
		value=val;
	}
	int getValue() {
		return value;
	}
	void setAces(int ace) {
		aces=ace;
	}
	int getAces() {
		return aces;
	}
};

class Dealer : public Player {
private:
	string hidden;
public:
	Dealer()
	 :Player(), hidden(" ") {

	}
	void setHidden(string hid) {
		hidden=hid;
	}
	string getHidden() {
		return hidden;
	}
};

class Player1 : public Player {
private:
	int cash, bet, h, split, sn;
public:
	Player1()
	 :cash(100), bet(0), h(0), split(0) {

	}
	void setCash(int c) {
		cash=c;
	}
	int getCash() {
		return cash;
	}
	void setBet() {
		cin >> bet;
	}
	void setBet(int b) {
			bet=b;
		}
	int getBet() {
		return bet;
	}
	void setSN(int n) {
		sn=n;
	}
	int getSN() {
		return sn;
	}
	void setSplit(int s) {
		split=s;
	}
	int getSplit() {
		return split;
	}


};

int shuffle[313], i=0, game=1;
Card *cards[313];
Player1 *player1 = new Player1();
Dealer *dealer = new Dealer();

void nextMove(int, int, int);
void splitCards(int, int);

int retH() {
	int h=0;
	while (h!=1 && h!=2 && h!=3 && h!=4) {
		cin >> h;
	}
	return h;
}


void createCards() {
		int bjVal;
		string vc, vs;
		for (int c=1; c<313; c++) {
		switch (c%52) {
		case 1:
		case 2:
		case 3:
		case 4:
		{vc="Ace";	bjVal=11;}
		break;
		case 5:
		case 6:
		case 7:
		case 8:
	    {vc="King";	bjVal=10;}
	    break;
		case 9:
		case 10:
		case 11:
		case 12:
		{vc="Queen"; bjVal=10;}
		break;
		case 13:
		case 14:
		case 15:
		case 16:
		{vc="Jack";	bjVal=10;}
		break;
		case 17:
		case 18:
		case 19:
		case 20:
		{vc="Ten"; bjVal=10;}
		break;
		case 21:
		case 22:
		case 23:
		case 24:
		{vc="9"; bjVal=9;}
		break;
		case 25:
		case 26:
		case 27:
		case 28:
		{vc="8"; bjVal=8;}
		break;
		case 29:
		case 30:
		case 31:
		case 32:
		{vc="7"; bjVal=7;}
		break;
		case 33:
		case 34:
		case 35:
		case 36:
		{vc="6"; bjVal=6;}
		break;
		case 37:
		case 38:
		case 39:
		case 40:
		{vc="5"; bjVal=5;}
		break;
		case 41:
		case 42:
		case 43:
		case 44:
		{vc="4"; bjVal=4;}
		break;
		case 45:
		case 46:
		case 47:
		case 48:
		{vc="3"; bjVal=3;}
		break;
		case 49:
		case 50:
		case 51:
	    case 0:
	    {vc="2"; bjVal=2;}
		break;
		}

		switch (c%4) {
		case 1:
			vs="spade";
			break;
		case 2:
			vs="club";
			break;
		case 3:
			vs="heart";
			break;
		case 0:
			vs="diamond";
			break;
		}
		shuffle[c]=c;
		cards[c] = new Card (c, bjVal, vc, vs);
		//cards[c]->printCard();


	}
}



void shuffleCards() {
	int s1, s2, s3;
	srand(time(0));
	for (int si=0; si<10000; si++) {
			s1 = (rand()%312)+1;
			s2 = (rand()%312)+1;
			s3 = shuffle[s1];
			shuffle[s1] = shuffle[s2];
			shuffle[s2] = s3;
			}

	for (int sh=1,j; sh<313; sh++) {
		j=shuffle[sh];
		cards[j]->printCard();
	}
}

void dealCards() {
	int j, h, j1, j2;
	while (game) {  // main cycle(1)...
		player1->setValue(0);
		dealer->setValue(0);
		player1->setAces(0);
		dealer->setAces(0);
		player1->setSN(0);
		player1->setSplit(0);
		cout << "You have $" << player1->getCash() << ". Enter a bet amount: \n";
		if (player1->getCash()<1) { // if player doesn't have money(2)...
			cout << "Game over\n";
			game=0; // to avoid repeating of main cycle[1]
		}// ...(2)
		else { // if player has money to play(3)...
		player1->setBet();
		while (player1->getBet()>player1->getCash()) { // if player's bet is bigger than he can play(4)...
			cout << "You don't have enough $. Enter new bet amount: \n";
			player1->setBet();// enter another bet
		}// ...(4)
		player1->setCash(player1->getCash()-player1->getBet());
		j=shuffle[++i]; // reads id of next card in the deck and assign it to [j]
		if (cards[j]->cardname()[0]=='A') player1->setAces(player1->getAces()+1); // if ace has been dealt to player, counts it
		cout << "[Your] first card: \n__________" << cards[j]->cardname() << endl; // deals first card to player
		j1=j; // puts first card's id to [j1]
		player1->setValue(player1->getValue()+cards[j]->BJValue()); // adds dealt card's value to total value of player's cards
		j=shuffle[++i];
		if (cards[j]->cardname()[0]=='A') dealer->setAces(dealer->getAces()+1); // if ace has been dealt to dealer, counts it
		cout << "Dealer's first card: \n" << cards[j]->cardname() << endl; // deals first card to dealer
	    dealer->setValue(dealer->getValue()+cards[j]->BJValue()); // adds dealt card's value to total value of dealer's cards
     	j=shuffle[++i];
		if (cards[j]->cardname()[0]=='A') player1->setAces(player1->getAces()+1);
     	cout << "[Your] second card: \n__________" << cards[j]->cardname() << endl;
     	j2=j;
    	player1->setValue(player1->getValue()+cards[j]->BJValue());
    	if (cards[j1]->BJValue()==cards[j]->BJValue()) player1->setSplit(1); // compares first player's card to second one. if true then split is possible
    	j=shuffle[++i];
		if (cards[j]->cardname()[0]=='A') dealer->setAces(dealer->getAces()+1);
        dealer->setHidden(cards[j]->cardname());
	    cout << "Dealer's second card: \n" << "Hidden" << endl;
	    dealer->setValue(dealer->getValue()+cards[j]->BJValue());


	    if (player1->getValue()==21) { // if player has blackjack(5)...
	    	cout << "BlackJack!" << endl;
	    	if (dealer->getValue()==21) { // if both player and dealer have blackjack(19)...
	    						cout << "Dealer's second card:\n " << dealer->getHidden() << endl; // opens dealer's second card
	    						cout << "A tie\n";
	    						player1->setCash(player1->getCash()+player1->getBet());
	    					} // ... (19)
	    					else
	    						player1->setCash(player1->getCash()+(player1->getBet()*2.5));
	    }// ...(5)
	    else if (dealer->getValue()==21) { // if dealer has blackjack
	    	cout << "Dealer's second card:\n " << dealer->getHidden() << endl; // opens dealer's second card
			cout << "Dealer has BlackJack!";
	    }
	    else {
	    if (player1->getSplit()) {
	    	cout << "Hit(1)/stand(2)/double(3)/split(4): \n";
	    	h=retH();
	    	nextMove(h, j1, j2);
	    }
	    else {
	    	cout << "Hit(1)/stand(2)/double(3): \n";
	    	h=retH();
	    	nextMove(h, 0, 0);
	    }
	    }

} // ...(3)
} // ...(1)

}

void nextMove(int h, int sp1=0, int sp2=0) { // (6)...
	int j;

	if (h==4) {// if player splits

			 player1->setSN(player1->getSN()+1);
			 	if (player1->getSN()<4)
			 splitCards(sp1, sp2);
			 	else {
			 		cout << "You can't split more than 3 times in one hand\nHit(1)/stand(2)/double(3): \n" ;
			 		h=retH();

			 	}
		 }

	 if (h==3) {// if player doubles

		    player1->setCash(player1->getCash()-player1->getBet());
			player1->setBet(player1->getBet()*2);
	 		j=shuffle[++i];
	 		if (cards[j]->cardname()[0]=='A') player1->setAces(player1->getAces()+1);
	 		cout << "[Your] one more card: \n__________" << cards[j]->cardname() << endl;
	 		player1->setValue(player1->getValue()+cards[j]->BJValue());
	 		h=2;

	 		if (player1->getValue()>21) { // if player is busted(8)...
	 			if (player1->getAces()) { // if player has an ace(9)...
	 			player1->setValue(player1->getValue()-10); // change ace's value from 11 to 1
	 			player1->setAces(player1->getAces()-1); // discount this ace
	 			} // ...(9)
	 			else { // if player doesn't have any ace(10)...
	    			h=5; // to enter [h4] block
	 			} // ...(10)
	 		} // ...(8)

		 }

	 while (h==1) { // (7)...

		    		j=shuffle[++i];
		    		if (cards[j]->cardname()[0]=='A') player1->setAces(player1->getAces()+1);
		    		cout << "[Your] one more card: \n___________" << cards[j]->cardname() << endl;
		    		player1->setValue(player1->getValue()+cards[j]->BJValue());

		    		if (player1->getValue()>21) { // if player is busted(8)...
		    			if (player1->getAces()) { // if player has an ace(9)...
		    			player1->setValue(player1->getValue()-10); // change ace's value from 11 to 1
		    			player1->setAces(player1->getAces()-1); // discount this ace
		    			} // ...(9)
		    			else { // if player doesn't have any ace(10)...
		       			h=5; // to enter [h4] block
		    			} // ...(10)
		    		} // ...(8)

		    				    	if (h!=5) { // if not entering [h4] reads player's decision and assign it to [h]
		    				    		cout << "Hit(1)/stand(2): \n";
		    				    		cin >> h;
		    				    	}
		} // ...(7)
		//else


		if (h==2) { // if player wants to stand(11)...
				cout << "[Your] value is [" << player1->getValue() << "]\n"; // display the total value of player's cards
				// dealer's move
				cout << "Dealer's second card: \n" << dealer->getHidden() << endl; // display (turn over) second dealer's card
				while (dealer->getValue()<17) { // if dealer's total value smaller than 17(12)...
					//then he hits one more card
					j=shuffle[++i];
					if (cards[j]->cardname()[0]=='A') dealer->setAces(dealer->getAces()+1);
					cout << "Dealer's one more card: \n" << cards[j]->cardname() << endl;
			  		dealer->setValue(dealer->getValue()+cards[j]->BJValue());

			  				if (dealer->getValue()>21) { // if dealer is busted(13)...
			  					if (dealer->getAces()) { // if he has an ace(14)...
			  						dealer->setValue(dealer->getValue()-10); // changes it's value from 11 to 1
			  						dealer->setAces(dealer->getAces()-1); //discounts the ace
			  					} //...(14)
			  					else { // if dealer doesn't have an ace(15)...
			  					cout << "Dealer is busted!\n";
			  					} //...(15)
			  				} //... (13)
				} //...(12)
				cout << "Dealer's value is " << dealer->getValue() << endl;
				if (dealer->getValue()>21) player1->setCash(player1->getCash()+player1->getBet()*2);// pays to player

				// if both player and dealer stand then compares values of their cards
			if (dealer->getValue()<=21) { // checks if dealer is busted. if he doesn't then compares values(16)...
				if (player1->getValue()>dealer->getValue()) {
					cout << "You win!\n";
					player1->setCash(player1->getCash()+player1->getBet()*2);
				}
				else if (player1->getValue()<dealer->getValue()) {
					cout << "You lost\n";
				}
				else {
					cout << "A tie\n";
					player1->setCash(player1->getCash()+player1->getBet());
				}
			} // ...(16)
			} //... (11)




		if (h==5) { // if h=5, this is h5 block(18)...
				//if player is busted
			cout << "Busted!" << endl;
			} // ... (18)

	} // ...(6)

void splitCards(int c1, int c2) {
	int c3, c4, h;

	c3=shuffle[++i];
	c4=shuffle[++i];
	player1->setCash(player1->getCash()-player1->getBet());
	cout << "Round #1" << endl;
	player1->setValue(0);
	player1->setSplit(0);
	player1->setValue(cards[c1]->BJValue()+cards[c3]->BJValue());
	cout << "___[Your] first card is:\n" << cards[c1]->cardname() << "\n___[Your] second card is:\n" << cards[c3]->cardname() << endl;;
	if (cards[c1]->BJValue()==cards[c3]->BJValue())
		player1->setSplit(1);
	  if (player1->getSplit()) { //split=1
		    	if (cards[c1]->BJValue()!=11) { // if c1 is not the ace
		    		cout << "Hit(1)/stand(2)/double(3)/split(4):\n ";
		    		h=retH();
		    	}
		    	else {

		    			cout << "stand(2)/split(4):\n";
		    			h=retH();
		    			while (h!=2 && h!=4) {
		    				h=retH();
		    			}

		    	}

		    	nextMove(h, c1, c3);
		    }
		    else { // split=0
		    	if (cards[c1]->BJValue()!=11) { // if c1 is not the ace
		    			    		cout << "Hit(1)/stand(2)/double(3):\n ";
		    			    		h=retH();
		    			    		while (h==4)
		    			    		h=retH();
		    			    	}
		    			    	else {


		    			    				h=2;


		    			    	}

		    			    	nextMove(h, c1, c3);
		    }

	  cout << "Round #2" << endl;
	    player1->setValue(0);
	  	player1->setSplit(0);
	  	player1->setValue(cards[c2]->BJValue()+cards[c4]->BJValue());
		cout << "___[Your] first card is:\n" << cards[c2]->cardname() << "\n___[Your] second card is:\n" << cards[c4]->cardname() << endl;
	  	if (cards[c2]->BJValue()==cards[c4]->BJValue())
	  		player1->setSplit(1);
	    if (player1->getSplit()) { //split=1
	  		    	if (cards[c2]->BJValue()!=11) { // if c1 is not the ace
	  		    		cout << "Hit(1)/stand(2)/double(3)/split(4):\n ";
	  		    		h=retH();
	  		    	}
	  		    	else {

	  		    			cout << "stand(2)/split(4):\n";
	  		    			h=retH();
	  		    			while (h!=2 && h!=4) {
	  		    				h=retH();
	  		    			}

	  		    	}

	  		    	nextMove(h, c2, c4);
	  		    }
	  		    else { // split=0
	  		    	if (cards[c2]->BJValue()!=11) { // if c1 is not the ace
	  		    			    		cout << "Hit(1)/stand(2)/double(3):\n ";
	  		    			    		h=retH();
	  		    			    		while (h==4)
	  		    			    		h=retH();
	  		    			    	}
	  		    			    	else {



	  		    			    				h=2;


	  		    			    	}

	  		    			    	nextMove(h, c2, c4);
	  		    }

}


int main() {
	createCards();
	shuffleCards();
	dealCards();
	return 0;
}
