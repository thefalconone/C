import java.util.ArrayList;

public class Login{

	public ArrayList<User> UserList = new ArrayList<User>();
	public User user;

	void Login(String pseudo){
		UserList=getUserList();

		if(!isUnique(pseudo)){
			System.out.println("pseudo déjà pris");
		}
		else{
			user = new User(pseudo);
		}
	}

	void changerPseudo(String newPseudo){
		if(isUnique(newPseudo)){
			user.setPseudo(newPseudo);
		}
	}

	boolean isUnique(String pseudo){

		boolean unicite=true;

		for(User user : this.UserList){
			if(pseudo=user.getPseudo()){
				//unicité pas valide
				unicite=false;
			}
		}
		return unicite;
	}

	delSession
}