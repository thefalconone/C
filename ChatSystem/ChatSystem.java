import java.util.ArrayList;

public class ChatSystem{

	public ArrayList<User> UserList = new ArrayList<User>();
	public User user;

	ChatSystem{
		this.UserList=getUserList();
	}

	void Login(String pseudo){

		//test si le pseudo est déjà utilisé sur le reseau
		if(!isUnique(pseudo)){
			//UI Stuff
			System.out.println("pseudo déjà pris");
		}
		else{
			//a faire : charger l'user et son historique si il existe deja

			//création d'un nouveau user
			user = new User(pseudo, "127.0.0.1");
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
}