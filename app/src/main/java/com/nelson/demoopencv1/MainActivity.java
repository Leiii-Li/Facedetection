package com.nelson.demoopencv1;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.hardware.Camera;
import android.hardware.Camera.CameraInfo;
import android.hardware.Camera.PreviewCallback;
import android.os.Environment;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import com.nelson.demoopencv1.helper.CameraHelper;
import com.nelson.demoopencv1.helper.Utils;
import java.io.File;
import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity implements Callback, PreviewCallback {

    private OpencvHelper mOpencvHelper;
    private CameraHelper mCameraHelper;
    int cameraId = CameraInfo.CAMERA_FACING_BACK;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mOpencvHelper = new OpencvHelper();
        SurfaceView surfaceView = findViewById(R.id.surfaceView);
        surfaceView.getHolder().addCallback(this);
        mCameraHelper = new CameraHelper(cameraId);
        mCameraHelper.setPreviewCallback(this);

        Utils.copyAssets(this, "lbpcascade_frontalface.xml");

        initFaceData();
    }

    private void initFaceData() {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.face);
        int bytes = bitmap.getByteCount();

        ByteBuffer buf = ByteBuffer.allocate(bytes);
        bitmap.copyPixelsToBuffer(buf);

        byte[] byteArray = buf.array();
        mOpencvHelper.initFaceData(byteArray,bitmap.getWidth(),bitmap.getHeight());
    }

    @Override
    protected void onResume() {
        super.onResume();
        String path = new File(Environment.getExternalStorageDirectory(), "lbpcascade_frontalface.xml")
            .getAbsolutePath();
        mCameraHelper.startPreview();
        mOpencvHelper.init(path);

    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        mOpencvHelper.setSurface(holder.getSurface());
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        mOpencvHelper.postData(data, CameraHelper.WIDTH, CameraHelper.HEIGHT, cameraId);
    }
}
