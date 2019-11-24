

public class Session{

	public ArrayList<Message> historique = new ArrayList<Message>();
	public ArrayList<User> Participants = new ArrayList<User>();

	Session(ArrayList<User> Participants){
		this.Participants=Participants;
	}

	ArrayList<Messages> getHistorique(){
		return this.historique;
	}

	void receivedMsg(String txt){
		Message m = new Message(txt);
		this.historique.add(m);
		//à faire : update l'UI
	}

	void sendMsg(String txt){

		for(User user : this.Participants){
			send(user.getIP(), txt);
		}
	}
}