

public class Session{

	public ArrayList<Message> historique = new ArrayList<Message>();
	public ArrayList<User> UserListSession = new ArrayList<User>();

	Session(ArrayList<User> UserListSession){
		this.UserListSession=UserListSession;
	}

	ArrayList<Messages> getHistorique(){
		return this.historique;
	}

	void recievedMsg(String txt){
		Message m = new Message(txt);
		this.historique.add(m);
		//à faire : update l'UI
	}

	void sendMsg(String txt){

		for(User user : this.UserListSession){
			send(user.getIP(), txt);
		}
	}
}