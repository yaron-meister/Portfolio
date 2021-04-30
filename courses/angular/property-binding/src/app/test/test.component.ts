import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-test',
  template: `
  <h2>
    Welcome {{name}}
  </h2>
  <input [id]="myId" type="text" value="Yaron"> <!Property-binding>
  <input disabled={{isDisabled}} type="text" value="Yaron"> <!Interpulation doesn't work>
  <input [disabled]="isDisabled" type="text" value="Yaron"> <!Property binding do work>
  `,
  styleUrls: ['./test.component.css']
})
export class TestComponent implements OnInit {

  public name = "Meister";
  public myId = "testId";
  public isDisabled = false;
  constructor() { }

  ngOnInit(): void {
  }

}
