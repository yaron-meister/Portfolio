import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-two-way-binding',
  template: `
  <h2>
    <br>
    Welcome to {{twoWayBindingCompName}}
  </h2>
  <input [(ngModel)]="tWBName" type="text"> <!NG Model directive>
  {{tWBName}}
  `,
  styles: []
})
export class TwoWayBindingComponent implements OnInit {

  // Binding the input and output together (using in forms for example)
  // FormsModule was added in this tutor to app.module.ts
  public twoWayBindingCompName = "TWO-WAY-BINDING";
  public tWBName = "";

  constructor() { }

  ngOnInit(): void {
  }

}
