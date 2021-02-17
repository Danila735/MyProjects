package com.example.stringcalc;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onButtonClicked (View v)
    {
        EditText el = (EditText)findViewById(R.id.editText3);
        TextView resText = (TextView)findViewById(R.id.textView3);

//        resText.setText(el.getText().toString());
//        double res = Calculate.RPNtoAnswer(Calculate.ExpressionToRPN(el.getText().toString()));
        try
        {
            double res = Calculate.decide(el.getText().toString());
            String numberAsString = Double.toString(res);
            resText.setText(numberAsString);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
