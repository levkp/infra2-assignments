import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.Button;

public class Test extends Application {
    
    public static void main(String[] args) {
        System.out.println("Hello");
        launch(args);
    }

    @Override
	public void start(Stage stage) {

        Button b = new Button("Click me");
        stage.setScene(new Scene(b));
        stage.show();
	}
}
