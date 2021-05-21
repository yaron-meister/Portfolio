import { Component, OnInit } from '@angular/core';
import { HttpService } from '../http.service';

@Component({
  selector: 'app-http-using',
  template: `
  <h2>
    <br>
    Welcome to {{hUName}}
  </h2>
  <ul *ngFor="let employee of employees">
    <li>{{employee.name}}</li>
  </ul>
  `,
  styles: []
})
export class HttpUsingComponent implements OnInit {

  public hUName = "HTTP-USING";
  public employees = [];

  constructor(private _httpService: HttpService) { }

  ngOnInit(): void {
    this._httpService.getEmployees()
    .subscribe(data => this.employees = data); 
    // The left side of the '=>' is the argument of the function
    // The right side of the '=>' is the implementation of the function
  }
}
