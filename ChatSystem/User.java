import java.util.ArrayList;
import java.util.Objects;//hash codes

public class User{

	public String pseudo;
	public static String ip;
	public ArrayList<Session> SessionList = new ArrayList<Session>();

	User(String pseudo, String ip){
		this.pseudo=pseudo;
		this.ip=ip;
	}

	String getPseudo(){
		return this.pseudo;
	}

	void setPseudo(String newPseudo){
		this.pseudo=newPseudo;
	}

	String getIP(){
		return this.ip;
	}

	void delSession(int hashCode){
		for(Session session : this.SessionList){
			if(hashCode(session)=hashCode){
				SessionList.remove(session);
			}
		}
	}

	void newSession(ArrayList<User> UserListSession){
		Session session = new Session(UserListSession);
		SessionList.add(session);
	}

	void createNewSession(ArrayList<User> UserListSession){

		this.newSession(UserListSession);

		for(User user : this.UserListSession){
			send(user.getIP(), UserListSession);
		}
	}
}