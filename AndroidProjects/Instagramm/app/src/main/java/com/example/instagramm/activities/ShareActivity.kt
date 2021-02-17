package com.example.instagramm.activities

import android.content.Intent
import android.os.Bundle
import android.util.Log
import com.example.instagramm.R
import com.example.instagramm.models.FeedPost
import com.example.instagramm.models.User
import com.example.instagramm.utils.CameraHelper
import com.example.instagramm.utils.FireBaseHelper
import com.example.instagramm.utils.GlideApp
import com.example.instagramm.utils.ValueEventListenerAdapter
import kotlinx.android.synthetic.main.activity_share.*

class ShareActivity : BaseActivity(2) {
    private val TAG = "SharedActivity"
    private lateinit var mCamera: CameraHelper
    private lateinit var mFirebase: FireBaseHelper
    private lateinit var mUser: User

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_share)
        Log.d(TAG, "onCreate")

        mFirebase = FireBaseHelper(this)

        mCamera = CameraHelper(this)
        mCamera.takeCameraPicture()

        back_image.setOnClickListener { finish() }
        share_text.setOnClickListener { share() }

        mFirebase.currentUserReference().addValueEventListener(ValueEventListenerAdapter{
            mUser = it.asUser()!!
        })

    }


    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if (requestCode == mCamera.REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                GlideApp.with(this).load(mCamera.imageUri).centerCrop().into(post_image)
            } else {
                finish()
            }
        }
    }

    private fun share() {
        val imageUri = mCamera.imageUri
        if (imageUri != null) {
            val uid = mFirebase.currentUserUid()!!
            mFirebase.storage.child("users").child(uid).child("images")
                .child(imageUri.lastPathSegment.toString()).putFile(imageUri)
                .addOnCompleteListener {
                    if (it.isSuccessful) {
                        val imageDownloadUrl = it.result.downloadUrl!!.toString()
                        mFirebase.database.child("images").child(uid).push()
                            .setValue(imageDownloadUrl)
                            .addOnCompleteListener {
                                if (it.isSuccessful) {
                                    mFirebase.database.child("feed-posts").child(uid)
                                        .push()
                                        .setValue(mkFeedPost(uid, imageDownloadUrl))
                                        .addOnCompleteListener{
                                            if (it.isSuccessful){
                                                startActivity(Intent(this,
                                                    ProfileActivity::class.java))
                                                finish()
                                            }
                                        }
                                } else {
                                    showToast(it.exception!!.message!!)
                                }
                            }
                    } else {
                        showToast(it.exception!!.message!!)
                    }
                }
        }
    }

    private fun mkFeedPost(
        uid: String,
        imageDownloadUrl: String
    ): FeedPost {
        return FeedPost(
            uid = uid,
            username = mUser.username,
            image = imageDownloadUrl,
            caption = caption_input.text.toString(),
            photo = mUser.photo
        )
    }
}

