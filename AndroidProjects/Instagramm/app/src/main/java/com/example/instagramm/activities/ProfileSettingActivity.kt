package com.example.instagramm.activities

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.instagramm.R
import com.example.instagramm.utils.FireBaseHelper
import kotlinx.android.synthetic.main.activity_profile_settings.*

class ProfileSettingActivity : AppCompatActivity() {
    private lateinit var mFirebase: FireBaseHelper

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_profile_settings)

        mFirebase = FireBaseHelper(this)
        sign_out_text.setOnClickListener { mFirebase.auth.signOut() }
        back_image.setOnClickListener { finish() }
    }
}
