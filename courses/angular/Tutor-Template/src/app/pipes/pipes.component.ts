import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-pipes',
  template: `
  <h2>
    Welcome to {{pName}}
  </h2>

  <h2>{{pipesStr}}</h2>
  <h2>{{pipesStr | lowercase}}</h2>
  <h2>{{pipesStr | uppercase}}</h2>
  <h2>{{pipesMessage | titlecase}}</h2> <! Every first letter is capitalized >
  <h2>{{pipesStr | slice:3}}</h2>
  <h2>{{pipesStr | slice:3:7}}</h2>
  <h2>{{pipesPerson | json}}</h2>

  <! x.y-z > 
  <! x = num of integer digits >
  <! y = minimal digits after decimal point >
  <! z = maximal digits after decimal point >
  <h2>{{5.678 | number:'1.2-3'}}</h2> 
  <h2>{{5.678 | number:'3.4-5'}}</h2>
  <h2>{{5.678 | number:'3.1-2'}}</h2>

  <h2>{{0.25 | percent}}</h2>
  <h2>{{50 | currency}}</h2> <! By default - in US dollar >
  <h2>{{20 | currency: 'EUR'}}</h2> 
  <h2>{{20 | currency: 'EUR': 'code'}}</h2>
  
  <h2>{{ pipesDate }}</h2>
  <h2>{{pipesDate | date:'short'}}</h2>
  <h2>{{pipesDate | date:'shortDate'}}</h2>
  <h2>{{pipesDate | date:'shortTime'}}</h2>
  
`,
styles: []
})
export class PipesComponent implements OnInit {

  public pName = "PIPES";
  public pipesStr = "Hello Pipes";
  public pipesMessage = "welcome pipes";
  public pipesPerson = {
    "firstName": "Yaron",
    "lastName": "Meister"
  }

  public pipesDate = new Date();

  constructor() { }

  ngOnInit(): void {
  }

}
